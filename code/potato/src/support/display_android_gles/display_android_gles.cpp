#include <rapidjson/document.h>
#include <android/sensor.h>
#include <android_native_app_glue.h>

#include "display_android_gles.h"

#include "render.h"

#include "utility/util_file.h"
#include "utility/util_log.h"

#include <cassert>
#include <unistd.h>
#include <sys/time.h>

namespace ac {
namespace display {
namespace android_gles {

CDisplay::CDisplay(const ac::base::Config& roConfig)
  : m_pGLDisplay(EGL_NO_DISPLAY)
  , m_pGLSurface(EGL_NO_SURFACE)
  , m_pGLContext(EGL_NO_CONTEXT)
  , m_pGLConfig(NULL)
  , m_bIsInitialized(false)
  , m_bIsRunning(false), m_bIsEGLReady(false), m_bCanRender(false)
  , m_pRender(NULL)
  , m_pApp(NULL)
  , m_pAccelerometerSensor(NULL)
  , m_pAccelerometerSensorEventQueue(NULL)
{
  std::string file_context = utility::ReadFile(roConfig.GetConfigureFile());
  //
}

CDisplay::~CDisplay()
{
  ;
}

void CDisplay::BindRender(core::IRender*& rpRender)
{
  assert(NULL != rpRender && NULL == m_pRender);
  m_pRender = rpRender;
}

void CDisplay::BindAndroidApp(struct android_app* pApp)
{
  m_pApp = pApp;
}

static void handle_cmd(struct android_app* app, int32_t cmd)
{
  ac::display::android_gles::CDisplay* display_ptr = (ac::display::android_gles::CDisplay*) app->userData;
  assert(NULL != display_ptr);

  switch (cmd)
  {
  case APP_CMD_INPUT_CHANGED:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_INPUT_CHANGED");
    break;

  case APP_CMD_INIT_WINDOW:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_INIT_WINDOW");
    if (NULL != app->window)
    {
      display_ptr->Initialize(app);
    }
    break;

  case APP_CMD_TERM_WINDOW:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_TERM_WINDOW");
    display_ptr->Terminated();
    break;

  case APP_CMD_WINDOW_RESIZED:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_WINDOW_RESIZED");
    break;

  case APP_CMD_WINDOW_REDRAW_NEEDED:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_WINDOW_REDRAW_NEEDED");
    break;

  case APP_CMD_CONTENT_RECT_CHANGED:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_CONTENT_RECT_CHANGED");
    break;

  case APP_CMD_GAINED_FOCUS:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_GAINED_FOCUS");
    display_ptr->Continue();
    break;

  case APP_CMD_LOST_FOCUS:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_LOST_FOCUS");
    display_ptr->Pause();
    break;

  case APP_CMD_CONFIG_CHANGED:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_CONFIG_CHANGED");
    break;

  case APP_CMD_LOW_MEMORY:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_LOW_MEMORY");
    break;

  case APP_CMD_START:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_START");
    break;

  case APP_CMD_RESUME:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_RESUME");
    break;

  case APP_CMD_SAVE_STATE:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_SAVE_STATE");
    break;

  case APP_CMD_PAUSE:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_PAUSE");
    break;

  case APP_CMD_STOP:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_STOP");
    display_ptr->Stop();
    break;

  case APP_CMD_DESTROY:
    ac::utility::Log::Instance().Info("handle_cmd APP_CMD_DESTROY");
    break;
  }
}

static int32_t handle_input(struct android_app* app, AInputEvent* event)
{
  int32_t type = AInputEvent_getType(event);
  ac::utility::Log::Instance().Info("engine_handle_input %d", type);
  if (AINPUT_EVENT_TYPE_KEY == type)
  {
    int32_t action = AKeyEvent_getAction(event);
    ac::utility::Log::Instance().Info("handle_input action:%d", action);
  }
  else if (AINPUT_EVENT_TYPE_MOTION == type)
  {
    int32_t action = AMotionEvent_getAction(event);
    int32_t count = AMotionEvent_getPointerCount(event);
    for (int i = 0; i < count; ++i)
    {
      float raw_x = AMotionEvent_getRawX(event, i);
      float raw_y = AMotionEvent_getRawY(event, i);
      float x = AMotionEvent_getX(event, i);
      float y = AMotionEvent_getY(event, i);
      float pressure = AMotionEvent_getPressure(event, i);
      float size = AMotionEvent_getSize(event, i);

      ac::utility::Log::Instance().Info("handle_input %d action:%d raw:(%.3f, %.3f) | pos:(%.3f, %.3f) | pressure:%.3f | size:%.3f", i + 1, action, raw_x, raw_y, x, y, pressure, size);
    }
    return 1;
  }
  //
  return 0;
}

// NOTE: based on the file 'android-ndk-r10/sources/android/native_app_glue/android_native_app_glue.c'
// Android has a bug in this function
// I make it don't report error when receive and handle the input event
// But it still report error when don't handle the input event
static void process_input(struct android_app* app, struct android_poll_source* source)
{
  AInputEvent* event = NULL;
  while (AInputQueue_getEvent(app->inputQueue, &event) >= 0)
  {
    if (AInputQueue_preDispatchEvent(app->inputQueue, event))
    {
      continue;
    }

    int32_t handled = 0;
    if (app->onInputEvent != NULL) handled = app->onInputEvent(app, event);
    AInputQueue_finishEvent(app->inputQueue, event, handled);

    // FIXED: Need check the input queue again
    if (!AInputQueue_hasEvents(app->inputQueue))
    {
      break;
    }
  }
}

void CDisplay::Run()
{
  ac::utility::Log::Instance().Info("CDisplay::Run");
  assert(NULL != m_pRender);
  assert(NULL != m_pApp);
  m_bIsRunning = true;
  m_bCanRender = true;

  m_pApp->userData = this;
  m_pApp->onAppCmd = handle_cmd;
  m_pApp->onInputEvent = handle_input;
  m_pApp->inputPollSource.process = process_input;

  ASensorManager* sensor_manager_ptr = ASensorManager_getInstance();
  m_pAccelerometerSensor = ASensorManager_getDefaultSensor(sensor_manager_ptr, ASENSOR_TYPE_ACCELEROMETER);
  m_pAccelerometerSensorEventQueue = ASensorManager_createEventQueue(sensor_manager_ptr, m_pApp->looper, LOOPER_ID_USER, NULL, NULL);
  ac::utility::Log::Instance().Info("%d %d", (int)m_pAccelerometerSensor, (int)m_pAccelerometerSensorEventQueue);

  timeval time;
  gettimeofday(&time, NULL);
  double second = time.tv_sec * 1.0 + time.tv_usec / 1000000.0;
  double second_temp = 0.0;
  double second_delta = 0.0;
  double second_sleep = 0.0;
  double second_per_frame_min = 1.0 / 60.0;
  //int count = 0;

  int ident = 0;
  int events = 0;
  android_poll_source* source = NULL;
  ASensorEvent accelerometer_sensor_event;

  while (m_bIsRunning)
  {
    ident = 0;
    events = 0;
    source = NULL;

    // If not running, we will block forever waiting for events.
    // If running, we loop until all events are read, then continue to draw the next frame.
    while ((ident = ALooper_pollAll(m_bIsRunning ? 0 : -1, NULL, &events, (void**) &source)) >= 0)
    {
      // Process this event.
      if (source != NULL)
      {
        source->process(m_pApp, source);
      }

      // If a sensor has data, process it now.
      if (ident == LOOPER_ID_USER)
      {
        if (m_pAccelerometerSensor != NULL)
        {
          while (ASensorEventQueue_getEvents(m_pAccelerometerSensorEventQueue, &accelerometer_sensor_event, 1) > 0)
          {
            ac::utility::Log::Instance().Info("vec: x=%.3f y=%.3f z=%.3f | acc: x=%.3f y=%.3f z=%.3f  mag: x=%.3f y=%.3f z=%.3f"
                , accelerometer_sensor_event.vector.x, accelerometer_sensor_event.vector.y, accelerometer_sensor_event.vector.z
                , accelerometer_sensor_event.acceleration.x, accelerometer_sensor_event.acceleration.y, accelerometer_sensor_event.acceleration.z
                , accelerometer_sensor_event.magnetic.x, accelerometer_sensor_event.magnetic.y, accelerometer_sensor_event.magnetic.z);
          }
        }
      }

      // Check if we are exiting.
      if (m_pApp->destroyRequested != 0)
      {
        //Stop();
        //break;
        Terminated();
        break;
        //return;
      }
    }

    if (m_bIsRunning && m_bIsEGLReady && m_bCanRender)
    {
      gettimeofday(&time, NULL);
      second_temp = second;
      second = time.tv_sec * 1.0 + time.tv_usec / 1000000.0;
      second_delta = second - second_temp;
      if (m_pRender->Render(static_cast<float>(second_delta), NULL))
      {
        eglSwapBuffers(m_pGLDisplay, m_pGLSurface);
      }

      gettimeofday(&time, NULL);
      second_sleep = second_per_frame_min - (time.tv_sec * 1.0 + time.tv_usec / 1000000.0 - second);
      if (0.001 < second_sleep)
      {
        //ac::utility::Log::Instance().Info("%d time: s-%f | temp-%f | delta-%f | spf-%f | sleep-%f\n", ++count, second, second_temp, second_delta, second_per_frame_min, second_sleep);
        usleep(static_cast<__useconds_t >(second_sleep * 1000000));
      }
    }
  }
}

void CDisplay::Initialize(android_app* pApp)
{
  ac::utility::Log::Instance().Info("CDisplay::Initialize");
  m_pGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  ac::utility::Log::Instance().Info("display: %d", (int) m_pGLDisplay);
  assert(EGL_NO_DISPLAY != m_pGLDisplay);

  EGLint egl_major = 0;
  EGLint egl_minor = 0;
  if (EGL_TRUE != eglInitialize(m_pGLDisplay, &egl_major, &egl_minor))
  assert(0);
  ac::utility::Log::Instance().Info("using EGL v%d.%d", egl_major, egl_minor);

  const EGLint config_attribs[] = {
  EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
  EGL_RED_SIZE, 8,
  EGL_GREEN_SIZE, 8,
  EGL_BLUE_SIZE, 8,
  EGL_ALPHA_SIZE, 8,
  EGL_BUFFER_SIZE, 32,
  EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
  EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
  EGL_NONE };
  EGLint num_configs = 0;
  if (!eglChooseConfig(m_pGLDisplay, config_attribs, &m_pGLConfig, 1, &num_configs))
  {
    assert(0);
  }
  assert(NULL != m_pGLConfig && num_configs > 0);

  EGLint vid = 0;
  eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_NATIVE_VISUAL_ID, &vid);

  ANativeWindow_setBuffersGeometry(pApp->window, 0, 0, vid);

  m_pGLSurface = eglCreateWindowSurface(m_pGLDisplay, m_pGLConfig, (EGLNativeWindowType) pApp->window, NULL);
  assert(EGL_NO_SURFACE != m_pGLSurface);

  const EGLint context_attribs[] = {
  EGL_CONTEXT_CLIENT_VERSION, 1,
  EGL_NONE };
  m_pGLContext = eglCreateContext(m_pGLDisplay, m_pGLConfig, NULL, context_attribs);
  assert(EGL_NO_DISPLAY != m_pGLContext);
  if (EGL_TRUE != eglMakeCurrent(m_pGLDisplay, m_pGLSurface, m_pGLSurface, m_pGLContext))
  assert(0);

  m_pRender->Start();

  EGLint width = 0;
  EGLint height = 0;
  eglQuerySurface(m_pGLDisplay, m_pGLSurface, EGL_WIDTH, &width);
  eglQuerySurface(m_pGLDisplay, m_pGLSurface, EGL_HEIGHT, &height);

  m_pRender->Resize(width, height);

  m_bIsInitialized = true;
  m_bIsEGLReady = true;
}

void CDisplay::Terminated()
{
  if (!m_bIsInitialized)
  {
    return;
  }
  ac::utility::Log::Instance().Info("CDisplay::Terminated");

  m_pRender->End();

  if (m_pGLDisplay != EGL_NO_DISPLAY && m_bIsEGLReady)
  {
    eglMakeCurrent(m_pGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE,
    EGL_NO_CONTEXT);
    if (m_pGLContext != EGL_NO_CONTEXT)
    {
      eglDestroyContext(m_pGLDisplay, m_pGLContext);
      m_pGLContext = EGL_NO_CONTEXT;
    }
    if (m_pGLSurface != EGL_NO_SURFACE)
    {
      eglDestroySurface(m_pGLDisplay, m_pGLSurface);
      m_pGLSurface = EGL_NO_SURFACE;
    }
    eglTerminate(m_pGLDisplay);
    m_pGLDisplay = EGL_NO_DISPLAY;
  }

  m_bIsInitialized = false;
  m_bIsRunning = false;
  m_bIsEGLReady = false;
  m_bCanRender = false;
}

void CDisplay::Continue()
{
  ac::utility::Log::Instance().Info("CDisplay::Continue");
  if (NULL != m_pAccelerometerSensor)
  {
      ASensorEventQueue_enableSensor(m_pAccelerometerSensorEventQueue, m_pAccelerometerSensor);
      // We'd like to get 60 events per second (in us).
      ASensorEventQueue_setEventRate(m_pAccelerometerSensorEventQueue, m_pAccelerometerSensor, (1000000L/3));
  }
  m_bCanRender = true;
}

void CDisplay::Pause()
{
  ac::utility::Log::Instance().Info("CDisplay::Pause");

  if (NULL != m_pAccelerometerSensor)
  {
      ASensorEventQueue_disableSensor(m_pAccelerometerSensorEventQueue, m_pAccelerometerSensor);
  }

  m_bCanRender = false;
}

void CDisplay::Stop()
{
  ac::utility::Log::Instance().Info("CDisplay::Stop");
}

void CDisplay::Resize(const int& riWidth, const int& riHeight)
{
  m_pRender->Resize(riWidth, riHeight);
}

}
}
}

bool CreateDisplay(ac::core::IDisplay*& rpDisplay, const ac::base::Config& roConfig)
{
  assert(rpDisplay == NULL);
  rpDisplay = new ac::display::android_gles::CDisplay(roConfig);
  return true;
}

bool DestroyDisplay(ac::core::IDisplay*& rpDisplay, const ac::base::Config& roConfig)
{
  assert(rpDisplay != NULL);
  delete rpDisplay;
  rpDisplay = NULL;
  return true;
}

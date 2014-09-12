#include <rapidjson/document.h>
#include <android/sensor.h>
#include <android/window.h>
#include <android_native_app_glue.h>

#include "display_android_gles.h"

#include "render.h"
#include "scene.h"

#include "utility/file.h"
#include "utility/log.h"
#include "utility/sharedlibrary.h"

#include <cassert>
#include <unistd.h>
#include <sys/time.h>

FUNC_API_TYPEDEF(CreateRender, c4g::core::IRender, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyRender, c4g::core::IRender, const c4g::base::Config);

namespace c4g {
namespace display {
namespace android_gles {

CDisplay::CDisplay(const base::Config& roConfig)
  : m_pGLDisplay(EGL_NO_DISPLAY)
  , m_pGLSurface(EGL_NO_SURFACE)
  , m_pGLContext(EGL_NO_CONTEXT)
  , m_pGLConfig(NULL)
  , m_bIsInitialized(false)
  , m_bIsRunning(false), m_bIsEGLReady(false), m_bCanRender(false)
  , m_pRender(NULL)
  , m_pScene(NULL)
  , m_pLibraryManager(NULL)
  , m_pApp(NULL)
  , m_pSensorManager(NULL)
  , m_pAccelerometerSensor(NULL)
  , m_pAccelerometerSensorEventQueue(NULL)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_pLibraryManager = new utility::CSharedLibraryManager();

#if defined(BUILD_ANDROID)
  std::string file_context = roConfig._sConfigureContext.c_str();
#else
  std::string file_context = utility::ReadFile(roConfig.GetConfigureFile());
#endif

  rapidjson::Document jdoc;
  jdoc.Parse(file_context.c_str());
  assert(jdoc.IsObject());

  m_oConfigRender._sLibrPath = roConfig._sLibrPath;
  m_oConfigRender._sDataPath = roConfig._sDataPath;

  const rapidjson::Value& render = jdoc["render"];
  assert(render.IsObject());
  const rapidjson::Value& library = render["library"];
  m_oConfigRender._sLibraryFile = library.GetString();

#if defined(BUILD_ANDROID)
  m_oConfigRender._sConfigureContext = "\
{\
\"render\":{\
  \"library\":\"lib/librender_gles.so\"\
}\
}";
#else
  assert(library.IsString());
  const rapidjson::Value& configure = render["configure"];
  assert(configure.IsString());
  m_oConfigRender._sConfigureFile = configure.GetString();
#endif

  typedef FUNC_API_TYPE(CreateRender) CreateRenderFuncPtr;
  /// load the shared library
  CreateRenderFuncPtr func_create_func_ptr = m_pLibraryManager->GetFunc<CreateRenderFuncPtr>(m_oConfigRender.GetLibraryFile(), TOSTRING(CreateRender));
  /// create the display with configure
  func_create_func_ptr(m_pRender, m_oConfigRender);
}

CDisplay::~CDisplay()
{
  /// load the shared library
  typedef FUNC_API_TYPE(DestroyRender) DestroyRenderFuncPtr;
  DestroyRenderFuncPtr func_destroy_func_ptr = m_pLibraryManager->GetFunc<DestroyRenderFuncPtr>(m_oConfigRender.GetLibraryFile(), TOSTRING(DestroyRender));
  /// create the display with configure
  func_destroy_func_ptr(m_pRender, m_oConfigRender);

  delete m_pLibraryManager;
  m_pLibraryManager = NULL;

  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

void CDisplay::BindAndroidApp(struct android_app* pApp)
{
  m_pApp = pApp;
}

static void handle_cmd(struct android_app* app, int32_t cmd)
{
  display::android_gles::CDisplay* display_ptr = (display::android_gles::CDisplay*) app->userData;
  assert(NULL != display_ptr);

  switch (cmd)
  {
  case APP_CMD_INPUT_CHANGED:
    utility::Log::Instance().Info("handle_cmd APP_CMD_INPUT_CHANGED");
    break;

  case APP_CMD_INIT_WINDOW:
    utility::Log::Instance().Info("handle_cmd APP_CMD_INIT_WINDOW");
    if (NULL != app->window)
    {
      display_ptr->Initialize(app);
    }
    break;

  case APP_CMD_TERM_WINDOW:
    utility::Log::Instance().Info("handle_cmd APP_CMD_TERM_WINDOW");
    display_ptr->Terminated();
    break;

  case APP_CMD_WINDOW_RESIZED: {
    utility::Log::Instance().Info("handle_cmd APP_CMD_WINDOW_RESIZED");
    int width = ANativeWindow_getWidth(app->window);
    int height = ANativeWindow_getHeight(app->window);
    display_ptr->Resize(width, height);
  } break;

  case APP_CMD_WINDOW_REDRAW_NEEDED:
    utility::Log::Instance().Info("handle_cmd APP_CMD_WINDOW_REDRAW_NEEDED");
    break;

  case APP_CMD_CONTENT_RECT_CHANGED:
    utility::Log::Instance().Info("handle_cmd APP_CMD_CONTENT_RECT_CHANGED");
    break;

  case APP_CMD_GAINED_FOCUS:
    utility::Log::Instance().Info("handle_cmd APP_CMD_GAINED_FOCUS");
    display_ptr->Continue();
    break;

  case APP_CMD_LOST_FOCUS:
    utility::Log::Instance().Info("handle_cmd APP_CMD_LOST_FOCUS");
    display_ptr->Pause();
    break;

  case APP_CMD_CONFIG_CHANGED:
    utility::Log::Instance().Info("handle_cmd APP_CMD_CONFIG_CHANGED");
    break;

  case APP_CMD_LOW_MEMORY:
    utility::Log::Instance().Info("handle_cmd APP_CMD_LOW_MEMORY");
    break;

  case APP_CMD_START:
    utility::Log::Instance().Info("handle_cmd APP_CMD_START");
    break;

  case APP_CMD_RESUME:
    utility::Log::Instance().Info("handle_cmd APP_CMD_RESUME");
    break;

  case APP_CMD_SAVE_STATE:
    utility::Log::Instance().Info("handle_cmd APP_CMD_SAVE_STATE");
    break;

  case APP_CMD_PAUSE:
    utility::Log::Instance().Info("handle_cmd APP_CMD_PAUSE");
    break;

  case APP_CMD_STOP:
    utility::Log::Instance().Info("handle_cmd APP_CMD_STOP");
    display_ptr->Stop();
    break;

  case APP_CMD_DESTROY:
    utility::Log::Instance().Info("handle_cmd APP_CMD_DESTROY");
    break;
  }
}

static int32_t handle_input(struct android_app* app, AInputEvent* event)
{
  display::android_gles::CDisplay* display_ptr = (display::android_gles::CDisplay*) app->userData;
  assert(NULL != display_ptr);

  int32_t type = AInputEvent_getType(event);
  utility::Log::Instance().Info("engine_handle_input %d", type);
  if (AINPUT_EVENT_TYPE_KEY == type)
  {
    int32_t action = AKeyEvent_getAction(event);
    utility::Log::Instance().Info("handle_input action:%d", action);

    display_ptr->Input();
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

      utility::Log::Instance().Info("handle_input %d action:%d raw:(%.3f, %.3f) | pos:(%.3f, %.3f) | pressure:%.3f | size:%.3f", i + 1, action, raw_x, raw_y, x, y, pressure, size);
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

void CDisplay::Run(core::IScene* const& rpScene)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
  assert(NULL != m_pRender);
  assert(NULL != m_pApp);
  assert(NULL != rpScene);

  m_pScene = rpScene;

  m_bIsRunning = true;
  m_bCanRender = true;

  m_pApp->userData = this;
  m_pApp->onAppCmd = handle_cmd;
  m_pApp->onInputEvent = handle_input;
  m_pApp->inputPollSource.process = process_input;

  ANativeActivity_setWindowFlags(m_pApp->activity, AWINDOW_FLAG_FULLSCREEN | AWINDOW_FLAG_DITHER, 0);

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
            C4G_LOG_INFO("vec: x=%.3f y=%.3f z=%.3f | acc: x=%.3f y=%.3f z=%.3f  mag: x=%.3f y=%.3f z=%.3f"
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
      if (m_pRender->Render(static_cast<float>(second_delta), rpScene))
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
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
  m_pGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  utility::Log::Instance().Info("display: %d", (int) m_pGLDisplay);
  assert(EGL_NO_DISPLAY != m_pGLDisplay);

  EGLint egl_major = 0;
  EGLint egl_minor = 0;
  if (EGL_TRUE != eglInitialize(m_pGLDisplay, &egl_major, &egl_minor))
  assert(0);
  utility::Log::Instance().Info("using EGL v%d.%d", egl_major, egl_minor);

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
  if (EGL_TRUE != eglMakeCurrent(m_pGLDisplay, m_pGLSurface, m_pGLSurface, m_pGLContext)) assert(0);

  m_pRender->Start();

  //TODO:
  m_pScene->Load(m_pRender, "scene/root.json");

  int width = ANativeWindow_getWidth(pApp->window);
  int height = ANativeWindow_getHeight(pApp->window);
  Resize(width, height);

  m_bIsInitialized = true;
  m_bIsEGLReady = true;

  m_pSensorManager = ASensorManager_getInstance();
  if (NULL != m_pSensorManager)
  {
    m_pAccelerometerSensor = ASensorManager_getDefaultSensor(m_pSensorManager, ASENSOR_TYPE_ACCELEROMETER);
    if (NULL != m_pAccelerometerSensor)
    {
      m_pAccelerometerSensorEventQueue = ASensorManager_createEventQueue(m_pSensorManager, m_pApp->looper, LOOPER_ID_USER, NULL, NULL);
      C4G_LOG_INFO("AccelerometerSensor %d %d", (int)m_pAccelerometerSensor, (int)m_pAccelerometerSensorEventQueue);
    }
    else
    {
      m_pAccelerometerSensorEventQueue = NULL;
    }
  }
}

void CDisplay::Terminated()
{
  if (!m_bIsInitialized)
  {
    return;
  }
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  if (NULL != m_pSensorManager)
  {
    if (NULL != m_pAccelerometerSensor)
    {
      if (NULL != m_pAccelerometerSensorEventQueue)
      {
        ASensorManager_destroyEventQueue(m_pSensorManager, m_pAccelerometerSensorEventQueue);
        m_pAccelerometerSensorEventQueue = NULL;
      }
      m_pAccelerometerSensor = NULL;
    }
    m_pSensorManager = NULL;
  }

  if (NULL != m_pScene)
  {
    m_pScene->Unload(m_pRender);
  }
  if (NULL != m_pRender)
  {
    m_pRender->End();
  }

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
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
  if (NULL != m_pAccelerometerSensor)
  {
    ASensorEventQueue_enableSensor(m_pAccelerometerSensorEventQueue, m_pAccelerometerSensor);
    // We'd like to get 60 events per second (in us).
    ASensorEventQueue_setEventRate(m_pAccelerometerSensorEventQueue, m_pAccelerometerSensor, 1000000);
    //ASensorEventQueue_setEventRate(m_pAccelerometerSensorEventQueue, m_pAccelerometerSensor, ASensor_getMinDelay(m_pAccelerometerSensor));
  }

  Run(m_pScene);
}

void CDisplay::Pause()
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  if (NULL != m_pAccelerometerSensor)
  {
      ASensorEventQueue_disableSensor(m_pAccelerometerSensorEventQueue, m_pAccelerometerSensor);
  }

  m_bCanRender = false;
}

void CDisplay::Stop()
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

void CDisplay::Resize(const int& riWidth, const int& riHeight)
{
  utility::Log::Instance().Info("%s (%d, %d)", __PRETTY_FUNCTION__, riWidth, riHeight);
  if (NULL != m_pRender) m_pRender->Resize(riWidth, riHeight);
  if (NULL != m_pScene) m_pScene->Resize(riWidth, riHeight);
}

void CDisplay::Input()
{
  m_pScene->Handle(NULL);
}

}
}
}

bool CreateDisplay(c4g::core::IDisplay*& rpDisplay, const c4g::base::Config& roConfig)
{
  assert(rpDisplay == NULL);
  rpDisplay = new c4g::display::android_gles::CDisplay(roConfig);
  return true;
}

bool DestroyDisplay(c4g::core::IDisplay*& rpDisplay, const c4g::base::Config& roConfig)
{
  assert(rpDisplay != NULL);
  delete rpDisplay;
  rpDisplay = NULL;
  return true;
}

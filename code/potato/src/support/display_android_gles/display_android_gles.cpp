#include <rapidjson/document.h>
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

CDisplay::CDisplay(const ac::base::Config& roConfig) :
    m_pGLDisplay(EGL_NO_DISPLAY), m_pGLSurface(EGL_NO_SURFACE), m_pGLContext(EGL_NO_CONTEXT), m_pGLConfig(NULL), m_bIsRunning(false), m_bIsEGLReady(false), m_bCanRender(false), m_pRender(NULL)
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

static void handle_cmd(struct android_app* app, int32_t cmd)
{
  ac::display::CDisplay* display_ptr = (ac::display::CDisplay*)app->userData;
  assert(NULL != display_ptr);

  switch (cmd)
  {
  case APP_CMD_INPUT_CHANGED:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_INPUT_CHANGED");
    break;

  case APP_CMD_INIT_WINDOW:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_INIT_WINDOW");
    if (NULL != app->window)
    {
      display_ptr->Initialize(app);
    }
    break;

  case APP_CMD_TERM_WINDOW:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_TERM_WINDOW");
    display_ptr->Stop();
    break;

  case APP_CMD_WINDOW_RESIZED:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_WINDOW_RESIZED");
    break;

  case APP_CMD_WINDOW_REDRAW_NEEDED:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_WINDOW_REDRAW_NEEDED");
    break;

  case APP_CMD_CONTENT_RECT_CHANGED:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_CONTENT_RECT_CHANGED");
    break;

  case APP_CMD_GAINED_FOCUS:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_GAINED_FOCUS");
    display_ptr->Continue();
    break;

  case APP_CMD_LOST_FOCUS:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_LOST_FOCUS");
    display_ptr->Pause();
    break;

  case APP_CMD_CONFIG_CHANGED:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_CONFIG_CHANGED");
    break;

  case APP_CMD_LOW_MEMORY:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_LOW_MEMORY");
    break;

  case APP_CMD_START:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_START");
    break;

  case APP_CMD_RESUME:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_RESUME");
    break;

  case APP_CMD_SAVE_STATE:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_SAVE_STATE");
    break;

  case APP_CMD_PAUSE:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_PAUSE");
    break;

  case APP_CMD_STOP:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_STOP");
    break;

  case APP_CMD_DESTROY:
    ac::utility::Log::Instance().Info("engine_handle_cmd APP_CMD_DESTROY");
    break;
  }
}

static int32_t handle_input(struct android_app* app, AInputEvent* event)
{
  //
  ac::utility::Log::Instance().Info("engine_handle_input");
  return 0;
}

void CDisplay::Run(android_app* pApp)
{
  ac::utility::Log::Instance().Info("CDisplay::Run");
  m_bIsRunning = true;
  m_bCanRender = true;

  pApp->userData = this;
  pApp->onAppCmd = handle_cmd;
  pApp->onInputEvent = handle_input;

  timeval time;
  gettimeofday(&time, NULL);
  double second = time.tv_sec * 1.0 + time.tv_usec / 1000000.0;
  double second_temp = 0.0;
  double second_delta = 0.0;
  double second_sleep = 0.0;
  double second_per_frame_min = 1.0 / 60.0;
  //int count = 0;

  while (m_bIsRunning)
  {
    // Read all pending events.
    int ident;
    int events;
    struct android_poll_source* source;

    // If not animating, we will block forever waiting for events.
    // If animating, we loop until all events are read, then continue
    // to draw the next frame of animation.
    while ((ident=ALooper_pollAll(m_bIsRunning ? 0 : -1, NULL, &events, (void**)&source)) >= 0)
    {
      // Process this event.
      if (source != NULL)
      {
        source->process(pApp, source);
      }

      // If a sensor has data, process it now.
      if (ident == LOOPER_ID_USER) { ; }

      // Check if we are exiting.
      if (pApp->destroyRequested != 0)
      {
        Stop();
        m_bIsRunning = false;
        break;
      }
    }

    if (m_bIsRunning && m_bIsEGLReady && m_bCanRender)
    {
      gettimeofday(&time, NULL);
      second_temp = second;
      second = time.tv_sec * 1.0 + time.tv_usec / 1000000.0;
      second_delta = second - second_temp;
      if (m_pRender->Tick(second_delta))
      {
        eglSwapBuffers(m_pGLDisplay, m_pGLSurface);
      }

      gettimeofday(&time, NULL);
      second_sleep = second_per_frame_min - (time.tv_sec * 1.0 + time.tv_usec / 1000000.0 - second);
      if (0.001 < second_sleep)
      {
        //printf("%d time: s-%f | temp-%f | delta-%f | spf-%f | sleep-%f\n", ++count, second, second_temp, second_delta, second_per_frame_min, second_sleep);
        usleep(static_cast<__useconds_t >(second_sleep * 1000000));
      }
    }
  }

  m_pRender->End();
  //DestroyWindow();
}

void CDisplay::Initialize(android_app* pApp)
{
  ac::utility::Log::Instance().Info("CDisplay::Initialize");
  m_pGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  ac::utility::Log::Instance().Info("display: %d", (int)m_pGLDisplay);
  assert(EGL_NO_DISPLAY != m_pGLDisplay);

  EGLint egl_major = 0;
  EGLint egl_minor = 0;
  if (EGL_TRUE != eglInitialize(m_pGLDisplay, &egl_major, &egl_minor)) assert(0);
  ac::utility::Log::Instance().Info("using EGL v%d.%d", egl_major, egl_minor);

  const EGLint config_attribs[] = {
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_NONE
    };
  EGLint num_configs = 0;
  if (!eglChooseConfig(m_pGLDisplay, config_attribs, &m_pGLConfig, 1, &num_configs))
  {
    assert(0);
  }
  assert(NULL != m_pGLConfig && num_configs > 0);

  EGLint vid = 0;
  eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_NATIVE_VISUAL_ID, &vid);

  ANativeWindow_setBuffersGeometry(pApp->window, 0, 0, vid);

  m_pGLSurface = eglCreateWindowSurface(m_pGLDisplay, m_pGLConfig, pApp->window, NULL);
  assert(EGL_NO_SURFACE != m_pGLSurface);

  const EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 1,
    EGL_NONE };
  m_pGLContext = eglCreateContext(m_pGLDisplay, m_pGLConfig, NULL, context_attribs);
  assert(EGL_NO_DISPLAY != m_pGLContext);
  if (EGL_TRUE != eglMakeCurrent(m_pGLDisplay, m_pGLSurface, m_pGLSurface, m_pGLContext)) assert(0);

  m_pRender->Start();

  EGLint width = 0;
  EGLint height = 0;
  eglQuerySurface(m_pGLDisplay, m_pGLSurface, EGL_WIDTH, &width);
  eglQuerySurface(m_pGLDisplay, m_pGLSurface, EGL_HEIGHT, &height);

  m_pRender->Resize(width, height);

  m_bIsEGLReady = true;
}

void CDisplay::Stop()
{
  ac::utility::Log::Instance().Info("CDisplay::Stop");
  if (m_pGLDisplay != EGL_NO_DISPLAY && m_bIsEGLReady)
  {
    eglMakeCurrent(m_pGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
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

  m_bIsRunning = false;
  m_bIsEGLReady = false;
  m_bCanRender = false;
}

void CDisplay::Continue()
{
  ac::utility::Log::Instance().Info("CDisplay::Continue");
  m_bCanRender = true;
}

void CDisplay::Pause()
{
  ac::utility::Log::Instance().Info("CDisplay::Pause");
  m_bCanRender = false;
}

void CDisplay::Resize(const int& riWidth, const int& riHeight)
{
  m_pRender->Resize(riWidth, riHeight);
}

}
}

bool CreateDisplay(ac::core::IDisplay*& rpDisplay, const ac::base::Config& roConfig)
{
  assert(rpDisplay == NULL);
  rpDisplay = new ac::display::CDisplay(roConfig);
  return true;
}

bool DestroyDisplay(ac::core::IDisplay*& rpDisplay, const ac::base::Config& roConfig)
{
  assert(rpDisplay != NULL);
  delete rpDisplay;
  rpDisplay = NULL;
  return true;
}

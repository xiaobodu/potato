#include <rapidjson/document.h>

#include "display_android_gles.h"

#include "render.h"

#include "utility/util_file.h"

#include <cassert>
#include <unistd.h>
#include <sys/time.h>

namespace ac {
namespace display {

CDisplay::CDisplay(const ac::base::Config& roConfig) :
    m_pGLDisplay(EGL_NO_DISPLAY), m_pGLSurface(EGL_NO_SURFACE), m_pGLContext(EGL_NO_CONTEXT), m_pGLConfig(NULL), m_bIsRunning(true), m_pRender(NULL)
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

void CDisplay::Run()
{
  //Initialize(NULL);

  assert(NULL != m_pGLContext);
  //CreateWindow();
  m_pRender->Start();
  //m_pRender->Resize(m_pGLContext->GetScreenWidth(), m_pGLContext->GetScreenHeight());

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

  m_pRender->End();
  //DestroyWindow();
}

void CDisplay::Initialize(EGLNativeWindowType pWindow)
{
  m_pGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  assert(EGL_NO_DISPLAY != m_pGLDisplay);

  EGLint egl_major, egl_minor;
  assert(eglInitialize(m_pGLDisplay, &egl_major, &egl_minor));

  const EGLint attribs[] = {
    EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
    EGL_NONE };
  EGLint num_configs;
  assert(eglChooseConfig(m_pGLDisplay, attribs, &m_pGLConfig, 1, &num_configs));
  assert(NULL != m_pGLConfig && num_configs > 0);

  m_pGLSurface = eglCreateWindowSurface(m_pGLDisplay, m_pGLConfig, pWindow, NULL);
  assert(EGL_NO_SURFACE != m_pGLSurface);

  const EGLint context_attribs[] = {
    EGL_CONTEXT_CLIENT_VERSION, 1,
    EGL_NONE };
  m_pGLContext = eglCreateContext(m_pGLDisplay, m_pGLConfig, NULL, context_attribs);
  assert(EGL_NO_DISPLAY != m_pGLContext);
  assert(EGL_FALSE != eglMakeCurrent(m_pGLDisplay, m_pGLSurface, m_pGLSurface, m_pGLContext));
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

void android_main(struct android_app* app)
{
  //
}

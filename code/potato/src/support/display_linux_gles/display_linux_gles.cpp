#include <rapidjson/document.h>

#include "display_linux_gles.h"

#include "render.h"

#include "utility/util_file.h"

#include <cassert>
#include <unistd.h>
#include <sys/time.h>

namespace ac {
namespace display {

/*static int gs_aAttrList[] = { GLX_RGBA, GLX_DOUBLEBUFFER,
 GLX_RED_SIZE, 4,
 GLX_GREEN_SIZE, 4,
 GLX_BLUE_SIZE, 4,
 GLX_ALPHA_SIZE, 4,
 GLX_DEPTH_SIZE, 16,
 None };*/

CDisplay::CDisplay(const ac::base::Config& roConfig) :
    m_pDisplay(NULL), m_lWindow(0), m_pGLConfig(NULL), m_pGLDisplay(NULL), m_pGLContext(NULL), m_pGLSurface(
    NULL), m_bIsRunning(true), m_pRender(NULL)
{
  std::string file_context = utility::ReadFile(roConfig.GetConfigureFile());

  rapidjson::Document jdoc;
  jdoc.Parse(file_context.c_str());
  assert(jdoc.IsObject());
  const rapidjson::Value& jsize = jdoc["size"];
  assert(jsize.IsObject());
  const rapidjson::Value& jwidth = jsize["width"];
  assert(jwidth.IsInt());
  const rapidjson::Value& jheight = jsize["height"];
  assert(jheight.IsInt());

  m_iWidth = jwidth.GetInt();
  m_iHeight = jheight.GetInt();
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
  CreateWindow();
  m_pRender->Start();
  m_pRender->Resize(m_iWidth, m_iHeight);

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
    while (XPending(m_pDisplay) > 0)
    {
      static XEvent event;
      XNextEvent(m_pDisplay, &event);
      switch (event.type)
      {
      /*case Expose:
       if (event.xexpose.count != 0)
       {
       break;
       }
       if (m_pRender->Tick(second_delta))
       {
       glXSwapBuffers(m_pDisplay, m_lWindow);
       }
       break;*/

      case ConfigureNotify:
        if (event.xconfigure.width != m_iWidth || event.xconfigure.height != m_iHeight)
        {
          m_iWidth = event.xconfigure.width;
          m_iHeight = event.xconfigure.height;
          m_pRender->Resize(m_iWidth, m_iHeight);
        }
        break;

      case ButtonRelease:
        break;

      case KeyRelease:
        if (XK_Escape == XLookupKeysym(&event.xkey, 0))
        {
          m_bIsRunning = false;
        }
        break;
      }
    }

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
  DestroyWindow();
}

void CDisplay::CreateWindow()
{
  m_pDisplay = XOpenDisplay(NULL);
  assert(NULL != m_pDisplay);

  m_pGLDisplay = eglGetDisplay(m_pDisplay);
  assert(EGL_SUCCESS == eglGetError());

  EGLint egl_major, egl_minor;
  assert(eglInitialize(m_pGLDisplay, &egl_major, &egl_minor));

  static const EGLint attribs[] = {
  EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
  EGL_RED_SIZE, 8,
  EGL_GREEN_SIZE, 8,
  EGL_BLUE_SIZE, 8,
  EGL_ALPHA_SIZE, 8,
  EGL_BUFFER_SIZE, 32,
  EGL_DEPTH_SIZE, 8,
  EGL_STENCIL_SIZE, 1,
  EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
  EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
  EGL_NONE };

  int num_configs = 0;
  assert(eglChooseConfig(m_pGLDisplay, attribs, &m_pGLConfig, 1, &num_configs));
  assert(NULL != m_pGLConfig && num_configs > 0);

  int value = 0;
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_COLOR_BUFFER_TYPE, &value));
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_RED_SIZE, &value));
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_BUFFER_SIZE, &value));

  EGLint vid = 0;
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_NATIVE_VISUAL_ID, &vid));

  XVisualInfo* visual_info_ptr;
  XVisualInfo visual_info;
  visual_info.visualid = vid;
  int visual_number = 0;
  visual_info_ptr = XGetVisualInfo(m_pDisplay, VisualIDMask, &visual_info, &visual_number);
  assert(NULL != visual_info_ptr);

  Window root_window = RootWindow(m_pDisplay, DefaultScreen(m_pDisplay));
  XSetWindowAttributes attr;
  attr.background_pixel = 0;
  attr.border_pixel = 0;
  attr.colormap = XCreateColormap(m_pDisplay, root_window, visual_info_ptr->visual, AllocNone);
  attr.event_mask = StructureNotifyMask | ExposureMask | KeyReleaseMask | ButtonReleaseMask;
  unsigned long mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;
  m_lWindow = XCreateWindow(m_pDisplay, root_window, 0, 0, m_iWidth, m_iHeight, 0, visual_info_ptr->depth, InputOutput,
      visual_info_ptr->visual, mask, &attr);

  eglBindAPI(EGL_OPENGL_ES_API);

  m_pGLSurface = eglCreateWindowSurface(m_pGLDisplay, m_pGLConfig, m_lWindow, NULL);
  assert(NULL != m_pGLSurface);

  static const EGLint ctx_attribs[] = {
  EGL_NONE };
  m_pGLContext = eglCreateContext(m_pGLDisplay, m_pGLConfig, EGL_NO_CONTEXT, ctx_attribs);
  assert(NULL != m_pGLContext);

  //TODO: how to release all memory about x window
  XFree(visual_info_ptr);

  XMapWindow(m_pDisplay, m_lWindow);
  assert(eglMakeCurrent(m_pGLDisplay, m_pGLSurface, m_pGLSurface, m_pGLContext));
}

void CDisplay::DestroyWindow()
{
  eglDestroyContext(m_pGLDisplay, m_pGLContext);
  eglDestroySurface(m_pGLDisplay, m_pGLSurface);
  eglTerminate(m_pGLDisplay);

  XDestroyWindow(m_pDisplay, m_lWindow);
  XCloseDisplay(m_pDisplay);
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

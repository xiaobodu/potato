#include <rapidjson/document.h>

#include "display_linux_gles.h"

#include "render.h"

#include "utility/util_file.h"
#include "utility/util_log.h"

#include <cassert>
#include <unistd.h>
#include <sys/time.h>

namespace c4g {
namespace display {
namespace linux_gles {

CDisplay::CDisplay(const base::Config& roConfig)
  : m_pDisplay(NULL), m_lWindow(0), m_pGLConfig(NULL), m_pGLDisplay(EGL_NO_DISPLAY)
  , m_pGLContext(EGL_NO_CONTEXT), m_pGLSurface(EGL_NO_SURFACE), m_bIsRunning(true), m_pRender(NULL)
{
  std::string file_context = utility::ReadFile(roConfig.GetConfigureFile());

  rapidjson::Document jdoc;
  jdoc.Parse(file_context.c_str());
  assert(jdoc.IsObject());
  const rapidjson::Value& jtitle = jdoc["title"];
  assert(jtitle.IsString());
  const rapidjson::Value& jsize = jdoc["size"];
  assert(jsize.IsObject());
  const rapidjson::Value& jwidth = jsize["width"];
  assert(jwidth.IsInt());
  const rapidjson::Value& jheight = jsize["height"];
  assert(jheight.IsInt());

  m_sTitle = jtitle.GetString();
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
  utility::Log::Instance().Info("%s", __PRETTY_FUNCTION__);
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
    if (m_pRender->Render(static_cast<float>(second_delta), NULL))
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
  assert(EGL_NO_DISPLAY != m_pGLDisplay);
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
    EGL_DEPTH_SIZE, 32,
    EGL_STENCIL_SIZE, 1,
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
    EGL_NONE };

  int num_configs = 0;
  assert(eglGetConfigs(m_pGLDisplay, &m_pGLConfig, 1, &num_configs));
  //assert(eglChooseConfig(m_pGLDisplay, attribs, &m_pGLConfig, 1, &num_configs));
  assert(NULL != m_pGLConfig && num_configs > 0);

  /*int value = 0;
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_COLOR_BUFFER_TYPE, &value));
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_RED_SIZE, &value));
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_BUFFER_SIZE, &value));*/

  EGLint vid = 0;
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_NATIVE_VISUAL_ID, &vid));

  XVisualInfo* visual_info_ptr;
  XVisualInfo visual_info;
  visual_info.visualid = vid;
  int visual_number = 0;
  visual_info_ptr = XGetVisualInfo(m_pDisplay, VisualIDMask, &visual_info, &visual_number);
  assert(NULL != visual_info_ptr);

  Window root_window = RootWindow(m_pDisplay, DefaultScreen(m_pDisplay));
  int window_pos_x = 0;
  {
    int display_width = DisplayWidth(m_pDisplay, DefaultScreen(m_pDisplay));
    window_pos_x = (display_width - m_iWidth) / 2;
  }
  int window_pos_y = 0;
  {
    int display_height = DisplayHeight(m_pDisplay, DefaultScreen(m_pDisplay));
    window_pos_y = (display_height - m_iHeight) / 2;
  }

  XSetWindowAttributes attr;
  attr.background_pixel = 0;
  attr.border_pixel = 0;
  attr.colormap = XCreateColormap(m_pDisplay, root_window, visual_info_ptr->visual, AllocNone);
  attr.event_mask = StructureNotifyMask | ExposureMask | KeyReleaseMask | ButtonReleaseMask;
  unsigned long mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;
  m_lWindow = XCreateWindow(m_pDisplay, root_window, window_pos_x, window_pos_y, m_iWidth, m_iHeight, 0, visual_info_ptr->depth, InputOutput,
      visual_info_ptr->visual, mask, &attr);
  XSizeHints size_hints;
  size_hints.flags = PPosition | PSize | PMinSize;
  size_hints.x = window_pos_x;
  size_hints.y = window_pos_y;
  size_hints.width = m_iWidth;
  size_hints.height = m_iHeight;
  size_hints.min_width = m_iWidth;
  size_hints.min_height = m_iHeight;
  XSetStandardProperties(m_pDisplay, m_lWindow, m_sTitle.c_str(), None, None, 0, 0, &size_hints);

  eglBindAPI(EGL_OPENGL_ES_API);

  m_pGLSurface = eglCreateWindowSurface(m_pGLDisplay, m_pGLConfig, m_lWindow, NULL);
  assert(EGL_NO_SURFACE != m_pGLSurface);

  static const EGLint ctx_attribs[] = {
      EGL_CONTEXT_CLIENT_VERSION, 1,
      EGL_NONE };
  m_pGLContext = eglCreateContext(m_pGLDisplay, m_pGLConfig, EGL_NO_CONTEXT, ctx_attribs);
  assert(EGL_NO_CONTEXT != m_pGLContext);

  //TODO: how to release all memory about x window
  XFree(visual_info_ptr);

  XMapWindow(m_pDisplay, m_lWindow);
  assert(eglMakeCurrent(m_pGLDisplay, m_pGLSurface, m_pGLSurface, m_pGLContext));
}

void CDisplay::DestroyWindow()
{
  if (EGL_NO_DISPLAY != m_pGLDisplay)
  {
    if (EGL_NO_CONTEXT != m_pGLContext) eglDestroyContext(m_pGLDisplay, m_pGLContext);
    if (EGL_NO_SURFACE != m_pGLSurface) eglDestroySurface(m_pGLDisplay, m_pGLSurface);
    eglTerminate(m_pGLDisplay);
  }

  if (NULL != m_pDisplay)
  {
    if (0 != m_lWindow) XDestroyWindow(m_pDisplay, m_lWindow);
    XCloseDisplay(m_pDisplay);
  }
}

}
}
}

bool CreateDisplay(c4g::core::IDisplay*& rpDisplay, const c4g::base::Config& roConfig)
{
  assert(rpDisplay == NULL);
  rpDisplay = new c4g::display::linux_gles::CDisplay(roConfig);
  return true;
}

bool DestroyDisplay(c4g::core::IDisplay*& rpDisplay, const c4g::base::Config& roConfig)
{
  assert(rpDisplay != NULL);
  delete rpDisplay;
  rpDisplay = NULL;
  return true;
}

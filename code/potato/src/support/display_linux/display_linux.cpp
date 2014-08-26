#include <rapidjson/document.h>

#include "display_linux.h"
#include "thread/thread.h"

#include "utility/util_file.h"
#include "utility/util_dl.h"

#include <cassert>
#include <unistd.h>
#include <sys/time.h>

#include <GL/glx.h>

FUNC_API_TYPEDEF(CreateRender, ac::core::IRender, const ac::base::Config);
FUNC_API_TYPEDEF(DestroyRender, ac::core::IRender, const ac::base::Config);

namespace ac{
namespace core{

static int gs_aAttrList[] = { GLX_RGBA, GLX_DOUBLEBUFFER,
    GLX_RED_SIZE, 4,
    GLX_GREEN_SIZE, 4,
    GLX_BLUE_SIZE, 4,
    GLX_ALPHA_SIZE, 4,
    GLX_DEPTH_SIZE, 16,
    None };

CDisplay::CDisplay(const ac::base::Config& roConfig)
  : m_pDisplay(NULL)
  , m_lWindow(0)
  , m_pContext(NULL)
  , m_bIsRunning(true)
  , m_pRender(NULL)
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

void CDisplay::BindRender(IRender*& rpRender)
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
      glXSwapBuffers(m_pDisplay, m_lWindow);
    }

    gettimeofday(&time, NULL);
    second_sleep = second_per_frame_min - (time.tv_sec * 1.0 + time.tv_usec / 1000000.0 - second);
    if (0.001 < second_sleep)
    {
      //printf("%d time: s-%f | temp-%f | delta-%f | spf-%f | sleep-%f\n", ++count, second, second_temp, second_delta, second_per_frame_min, second_sleep);
      usleep(static_cast<__useconds_t>(second_sleep * 1000000));
    }
  }

  m_pRender->End();
  DestroyWindow();
}

void CDisplay::CreateWindow()
{
  m_pDisplay = XOpenDisplay(NULL);
  assert(NULL != m_pDisplay);

  XVisualInfo* visual_info_ptr = glXChooseVisual(m_pDisplay, DefaultScreen(m_pDisplay), gs_aAttrList);
  assert(NULL != visual_info_ptr);

  XSetWindowAttributes attr;
  attr.colormap = XCreateColormap(m_pDisplay, RootWindow(m_pDisplay, visual_info_ptr->screen), visual_info_ptr->visual, AllocNone);
  attr.border_pixel = 0;
  attr.override_redirect = True;
  attr.event_mask = ExposureMask | KeyReleaseMask | ButtonReleaseMask | StructureNotifyMask;
  /// can't resize the window size
  //attr.do_not_propagate_mask = ResizeRedirectMask;
  m_lWindow = XCreateWindow(m_pDisplay, RootWindow(m_pDisplay, visual_info_ptr->screen), 0, 0, m_iWidth, m_iHeight, 0,
      visual_info_ptr->depth, InputOutput, visual_info_ptr->visual,
      CWBorderPixel | CWColormap | CWEventMask, &attr);
  XMapRaised(m_pDisplay, m_lWindow);

  m_pContext = glXCreateContext(m_pDisplay, visual_info_ptr, 0, GL_TRUE);
  //TODO: how to release all memory about x window
  XFree(visual_info_ptr);

  glXMakeCurrent(m_pDisplay, m_lWindow, m_pContext);
}

void CDisplay::DestroyWindow()
{
  glXMakeCurrent(m_pDisplay, None, NULL);
  glXDestroyContext(m_pDisplay, m_pContext);
  XDestroyWindow(m_pDisplay, m_lWindow);
  XCloseDisplay(m_pDisplay);
}

}
}

bool CreateDisplay(ac::core::IDisplay*& rpDisplay, const ac::base::Config& roConfig)
{
  assert(rpDisplay == NULL);
  rpDisplay = new ac::core::CDisplay(roConfig);
  return true;
}

bool DestroyDisplay(ac::core::IDisplay*& rpDisplay, const ac::base::Config& roConfig)
{
  assert(rpDisplay != NULL);
  delete rpDisplay;
  rpDisplay = NULL;
  return true;
}

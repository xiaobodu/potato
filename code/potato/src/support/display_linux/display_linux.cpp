#include <rapidjson/document.h>

#include "display_linux.h"
#include "utility/util_file.h"

#include <cassert>
#include <GL/glx.h>

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
  , m_iScreen(0)
  , m_pVisualInfo(NULL)
  , m_lWindow(0)
  , m_pContext(NULL)
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

  int width = jwidth.GetInt();
  int height = jheight.GetInt();

  m_pDisplay = XOpenDisplay(NULL);
  assert(NULL != m_pDisplay);

  m_iScreen = DefaultScreen(m_pDisplay);
  m_pVisualInfo = glXChooseVisual(m_pDisplay, m_iScreen, gs_aAttrList);
  assert(NULL != m_pVisualInfo);

  XSetWindowAttributes attr;
  attr.colormap = XCreateColormap(m_pDisplay, RootWindow(m_pDisplay, m_pVisualInfo->screen), m_pVisualInfo->visual, AllocNone);
  attr.border_pixel = 0;
  attr.override_redirect = True;
  attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
      StructureNotifyMask;
  m_lWindow = XCreateWindow(m_pDisplay, RootWindow(m_pDisplay, m_pVisualInfo->screen), 0, 0, width, height, 0,
      m_pVisualInfo->depth, InputOutput, m_pVisualInfo->visual,
      CWBorderPixel | CWColormap | CWEventMask, &attr);
  XMapRaised(m_pDisplay, m_lWindow);

  m_pContext = glXCreateContext(m_pDisplay, m_pVisualInfo, 0, GL_TRUE);

  glXMakeCurrent(m_pDisplay, m_lWindow, m_pContext);
}

CDisplay::~CDisplay()
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

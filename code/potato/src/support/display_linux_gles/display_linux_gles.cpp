#include <rapidjson/document.h>

#include "display_linux_gles.h"

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
namespace linux_gles {

CDisplay::CDisplay(const base::Config& roConfig)
  : m_pDisplay(NULL)
  , m_lWindow(0)
  , m_lProtocolsDeleteWindow(None)
  , m_pGLConfig(NULL)
  , m_pGLDisplay(EGL_NO_DISPLAY)
  , m_pGLContext(EGL_NO_CONTEXT)
  , m_pGLSurface(EGL_NO_SURFACE)
  , m_bIsRunning(true)
  , m_iWidth(0)
  , m_iHeight(0)
  , m_pRender(NULL)
  , m_pLibraryManager(NULL)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  m_pLibraryManager = new utility::CSharedLibraryManager();

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

  const rapidjson::Value& render = jdoc["render"];
  assert(render.IsObject());
  const rapidjson::Value& library = render["library"];
  assert(library.IsString());
  const rapidjson::Value& configure = render["configure"];
  assert(configure.IsString());

  m_sTitle = jtitle.GetString();
  m_iWidth = jwidth.GetInt();
  m_iHeight = jheight.GetInt();

  m_oConfigRender._sLibrPath = roConfig._sLibrPath;
  m_oConfigRender._sDataPath = roConfig._sDataPath;
  m_oConfigRender._sLibraryFile = library.GetString();
  m_oConfigRender._sConfigureFile = configure.GetString();

  /// load the shared library
  typedef FUNC_API_TYPE(CreateRender) CreateRenderFuncPtr;
  CreateRenderFuncPtr func_create_func_ptr = m_pLibraryManager->GetFunc<CreateRenderFuncPtr>(m_oConfigRender.GetLibraryFile(), TOSTRING(CreateRender));
  /// create the display with configure
  func_create_func_ptr(m_pRender, m_oConfigRender);
}

CDisplay::~CDisplay()
{
  /// load the CShared library
  typedef FUNC_API_TYPE(DestroyRender) DestroyRenderFuncPtr;
  DestroyRenderFuncPtr func_destroy_func_ptr = m_pLibraryManager->GetFunc<DestroyRenderFuncPtr>(m_oConfigRender.GetLibraryFile(), TOSTRING(DestroyRender));
  /// create the display with configure
  func_destroy_func_ptr(m_pRender, m_oConfigRender);

  delete m_pLibraryManager;
  m_pLibraryManager = NULL;

  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

void CDisplay::Run(core::IScene* const& rpScene)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  CreateWindow();

  m_pRender->Start();
  m_pRender->Resize(m_iWidth, m_iHeight);

  //TODO:
  rpScene->Load(m_pRender, "scene/root.json");
  rpScene->Resize(m_iWidth, m_iHeight);

#if !defined(BUILD_COVERALLS)
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

      case ClientMessage:
        if (event.xclient.data.l[0] == static_cast<long>(m_lProtocolsDeleteWindow))
        {
          m_bIsRunning = false;
        }
        break;

      case ConfigureNotify:
        if (event.xconfigure.width != m_iWidth || event.xconfigure.height != m_iHeight)
        {
          m_iWidth = event.xconfigure.width;
          m_iHeight = event.xconfigure.height;
          m_pRender->Resize(m_iWidth, m_iHeight);
          rpScene->Resize(m_iWidth, m_iHeight);
        }
        break;

      case ButtonPress:
        m_oInput.type = EInputType_Touch;
        m_oInput.event = EInputEvent_Down;
        (*m_oInput[C4G_INPUT_TOUCH_COUNT]) = 1;
        (*m_oInput[C4G_INPUT_TOUCH_X]) = static_cast<float>(event.xbutton.x);
        (*m_oInput[C4G_INPUT_TOUCH_Y]) = static_cast<float>(event.xbutton.y);
        (*m_oInput[C4G_INPUT_TOUCH_LEFT]) = static_cast<float>(event.xbutton.x_root);
        (*m_oInput[C4G_INPUT_TOUCH_TOP]) = static_cast<float>(event.xbutton.y_root);
        rpScene->Handle(&m_oInput);
        break;

      case ButtonRelease:
        m_oInput.type = EInputType_Touch;
        m_oInput.event = EInputEvent_Up;
        (*m_oInput[C4G_INPUT_TOUCH_COUNT]) = 1;
        (*m_oInput[C4G_INPUT_TOUCH_X]) = static_cast<float>(event.xbutton.x);
        (*m_oInput[C4G_INPUT_TOUCH_Y]) = static_cast<float>(event.xbutton.y);
        (*m_oInput[C4G_INPUT_TOUCH_LEFT]) = static_cast<float>(event.xbutton.x_root);
        (*m_oInput[C4G_INPUT_TOUCH_TOP]) = static_cast<float>(event.xbutton.y_root);
        rpScene->Handle(&m_oInput);
        break;

      case MotionNotify:
        m_oInput.type = EInputType_Touch;
        m_oInput.event = EInputEvent_Move;
        (*m_oInput[C4G_INPUT_TOUCH_COUNT]) = 1;
        (*m_oInput[C4G_INPUT_TOUCH_X]) = static_cast<float>(event.xbutton.x);
        (*m_oInput[C4G_INPUT_TOUCH_Y]) = static_cast<float>(event.xbutton.y);
        (*m_oInput[C4G_INPUT_TOUCH_LEFT]) = static_cast<float>(event.xbutton.x_root);
        (*m_oInput[C4G_INPUT_TOUCH_TOP]) = static_cast<float>(event.xbutton.y_root);
        rpScene->Handle(&m_oInput);
        break;

      case KeyPress:
        m_oInput.type = EInputType_Key;
        m_oInput.event = EInputEvent_Down;
        (*m_oInput[C4G_INPUT_KEY_TYPE]) = event.xkey.type;
        (*m_oInput[C4G_INPUT_KEY_KEYCODE]) = static_cast<int>(event.xkey.keycode);
        (*m_oInput[C4G_INPUT_KEY_SERIAL]) = static_cast<int>(event.xkey.serial);
        rpScene->Handle(&m_oInput);
        break;

      case KeyRelease:
        m_oInput.type = EInputType_Key;
        m_oInput.event = EInputEvent_Up;
        (*m_oInput[C4G_INPUT_KEY_TYPE]) = event.xkey.type;
        (*m_oInput[C4G_INPUT_KEY_KEYCODE]) = static_cast<int>(event.xkey.keycode);
        (*m_oInput[C4G_INPUT_KEY_SERIAL]) = static_cast<int>(event.xkey.serial);
        rpScene->Handle(&m_oInput);
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
    if (m_pRender->Render(static_cast<float>(second_delta), rpScene))
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
#endif

  rpScene->Unload(m_pRender);
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
  EGLBoolean res = eglInitialize(m_pGLDisplay, &egl_major, &egl_minor);
  assert(res);
  if (!res) return;

  int num_configs = 0;
  res = eglGetConfigs(m_pGLDisplay, &m_pGLConfig, 1, &num_configs);
  assert(res);
  //assert(eglChooseConfig(m_pGLDisplay, attribs, &m_pGLConfig, 1, &num_configs));
  assert(NULL != m_pGLConfig && num_configs > 0);

  /*int value = 0;
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_COLOR_BUFFER_TYPE, &value));
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_RED_SIZE, &value));
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_GREEN_SIZE, &value));
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_BLUE_SIZE, &value));
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_ALPHA_SIZE, &value));
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_BUFFER_SIZE, &value));
  assert(eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_DEPTH_SIZE, &value));*/

  EGLint vid = 0;
  res = eglGetConfigAttrib(m_pGLDisplay, m_pGLConfig, EGL_NATIVE_VISUAL_ID, &vid);
  assert(res);

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
  attr.event_mask = StructureNotifyMask | ExposureMask
      | EnterWindowMask | LeaveWindowMask
      | KeyPressMask | KeyReleaseMask
      | ButtonPressMask | ButtonReleaseMask
      | Button1MotionMask
      | ButtonMotionMask | PointerMotionMask;
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

  m_lProtocolsDeleteWindow = XInternAtom(m_pDisplay, "WM_DELETE_WINDOW", True);
  XSetWMProtocols(m_pDisplay, m_lWindow, &m_lProtocolsDeleteWindow, 1);

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

#if !defined(BUILD_COVERALLS)
  XMapWindow(m_pDisplay, m_lWindow);
  res = eglMakeCurrent(m_pGLDisplay, m_pGLSurface, m_pGLSurface, m_pGLContext);
  assert(res);
#endif
}

void CDisplay::DestroyWindow()
{
  if (EGL_NO_DISPLAY != m_pGLDisplay)
  {
#if !defined(BUILD_COVERALLS)
    eglMakeCurrent(m_pGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
#endif
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

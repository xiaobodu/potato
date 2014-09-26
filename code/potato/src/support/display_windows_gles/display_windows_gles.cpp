#include <rapidjson/document.h>

#include "display_windows_gles.h"

#include "render.h"
#include "scene.h"

#include "utility/file.h"
#include "utility/log.h"
#include "utility/sharedlibrary.h"

#include <cassert>
#include <gl/GL.h>
//#include <unistd.h>
//#include <sys/time.h>

FUNC_API_TYPEDEF(CreateRender, c4g::core::IRender, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyRender, c4g::core::IRender, const c4g::base::Config);

namespace c4g {
namespace display {
namespace windows_gles {

CDisplay::CDisplay(const base::Config& roConfig)
  : m_pRC(NULL)
  , m_pDC(NULL)
  , m_pWnd(NULL)
  , m_pInstance(NULL)
  , m_bIsRunning(true)
  , m_iWidth(0)
  , m_iHeight(0)
  , m_pRender(NULL)
  , m_pLibraryManager(NULL)
  , m_pScene(NULL)
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

  if (CreateOsWindow())
  {
    m_pRender->Start();
    m_pRender->Resize(m_iWidth, m_iHeight);

    m_pScene = rpScene;
    //TODO:
    rpScene->Load(m_pRender, "scene/root.json");
    rpScene->Resize(m_iWidth, m_iHeight);

    MSG msg;
    msg.hwnd = m_pWnd;
    msg.message = WM_USER;
    msg.wParam = MSGF_USER;
    msg.lParam = (LPARAM)this;
    DispatchMessage(&msg);

    bool is_running = true;
    while (is_running)
    {
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
        if (WM_QUIT == msg.message)
        {
          is_running = false;
        }
        else
        {
          TranslateMessage(&msg);
          DispatchMessage(&msg);
        }
      }
      else
      {
        if (m_pRender->Render(0, rpScene))
        {
          SwapBuffers(m_pDC);
        }
      }
    }
    rpScene->Unload(m_pRender);
    m_pScene = NULL;
    m_pRender->End();
  }

  DestroyOsWindow();
}


void CDisplay::Resize(const int& riWidth, const int& riHeight)
{
  m_iWidth = riWidth;
  m_iHeight = riHeight;
  if (NULL != m_pRender) m_pRender->Resize(m_iWidth, m_iHeight);
  if (NULL != m_pScene) m_pScene->Resize(m_iWidth, m_iHeight);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  static CDisplay* s_pDisplay = NULL;
  if (WM_USER == uMsg && MSGF_USER == wParam)
  {
    s_pDisplay = reinterpret_cast<CDisplay*>(lParam);
    return 0;
  }
  if (NULL != s_pDisplay)
  {
    switch (uMsg)
    {
    //case WM_ACTIVATE:

    case WM_CLOSE:
      PostQuitMessage(0);
      return 0;
    case WM_SIZE:
      s_pDisplay->Resize(LOWORD(lParam), HIWORD(lParam));
      return 0;
    }
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool CDisplay::CreateOsWindow()
{
  m_pInstance = GetModuleHandle(NULL);
  if (NULL == m_pInstance) return false;

  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = (WNDPROC) WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = m_pInstance;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "potato";
  //TODO:
  if (!RegisterClass(&wc))
  {
    return false;
  }
  RECT rect;
  rect.left = 0;
  rect.right = 480;
  rect.top = 0;
  rect.bottom = 800;
  DWORD dw_style = WS_OVERLAPPEDWINDOW;
  DWORD dw_exstyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  if (!AdjustWindowRectEx(&rect, dw_style, FALSE, dw_exstyle)) return false;

  m_pWnd = CreateWindowEx(dw_exstyle, "potato", "potato", dw_style, 0, 0, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, m_pInstance, this);
  if (NULL == m_pWnd) return false;
  m_pDC = GetDC(m_pWnd);
  if (NULL == m_pDC) return false;
  PIXELFORMATDESCRIPTOR pfd;
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cRedBits = 0;
  pfd.cRedShift = 0;
  pfd.cGreenBits = 0;
  pfd.cGreenShift = 0;
  pfd.cBlueBits = 0;
  pfd.cBlueShift = 0;
  pfd.cAlphaBits = 0;
  pfd.cAlphaShift = 0;
  pfd.cAccumBits = 0;
  pfd.cAccumRedBits = 0;
  pfd.cAccumGreenBits = 0;
  pfd.cAccumBlueBits = 0;
  pfd.cAccumAlphaBits = 0;
  pfd.cDepthBits = 32;
  pfd.cStencilBits = 0;
  pfd.cAuxBuffers = 0;
  pfd.iLayerType = PFD_MAIN_PLANE;
  pfd.bReserved = 0;
  pfd.dwLayerMask = 0;
  pfd.dwVisibleMask = 0;
  pfd.dwDamageMask = 0;
  int pixel_format = ChoosePixelFormat(m_pDC, &pfd);
  if (0 == pixel_format) return false;
  if (!SetPixelFormat(m_pDC, pixel_format, &pfd)) return false;
  m_pRC = wglCreateContext(m_pDC);
  if (NULL == m_pRC) return false;
  if (!wglMakeCurrent(m_pDC, m_pRC)) return false;

  ShowWindow(m_pWnd, SW_SHOW);
  return true;
}

void CDisplay::DestroyOsWindow()
{
  if (NULL != m_pRC)
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(m_pRC);
    m_pRC = NULL;
  }

  if (NULL != m_pDC)
  {
    ReleaseDC(m_pWnd, m_pDC);
    m_pDC = NULL;
  }
  if (NULL != m_pWnd)
  {
    DestroyWindow(m_pWnd);
  }
  if (NULL != m_pInstance)
  {
    UnregisterClass("potato", m_pInstance);
  }
}

}
}
}

bool CreateDisplay(c4g::core::IDisplay*& rpDisplay, const c4g::base::Config& roConfig)
{
  assert(rpDisplay == NULL);
  rpDisplay = new c4g::display::windows_gles::CDisplay(roConfig);
  return true;
}

bool DestroyDisplay(c4g::core::IDisplay*& rpDisplay, const c4g::base::Config& roConfig)
{
  assert(rpDisplay != NULL);
  delete rpDisplay;
  rpDisplay = NULL;
  return true;
}

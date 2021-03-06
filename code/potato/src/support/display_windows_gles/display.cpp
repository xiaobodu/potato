#include "display_impl.h"

#include "render.h"
#include "scene.h"

#include "utility/file.h"
#include "utility/log.h"
#include "utility/sharedlibrary.h"
#include "utility/datetime.h"

#include <cassert>
#include <gl/GL.h>
#include <windowsx.h>

namespace c4g {
namespace display {
namespace windows_gles {

CDisplay* CDisplay::instance_ptr = NULL;

CDisplay::CDisplay()
  : m_pRC(NULL)
  , m_pDC(NULL)
  , m_pWnd(NULL)
  , m_pInstance(NULL)
  , m_bIsRunning(true)
  , m_sTitle(ENGINE_NAME)
  , m_iWidth(480)
  , m_iHeight(800)
  , m_pRender(NULL)
  , m_pScene(NULL)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  CDisplay::instance_ptr = this;
}

CDisplay::~CDisplay()
{
  m_pRender = NULL;

  CDisplay::instance_ptr = NULL;

  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

bool CDisplay::Initialize(core::MString2Module& rmModule)
{
  m_pRender = core::IModule::Find<core::IRender>(rmModule, MODULE_TYPE_RENDER);
  //
  return true;
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

#if !defined(BUILD_COVERALLS)
    MSG msg;
    msg.hwnd = m_pWnd;
    msg.message = WM_USER;
    msg.wParam = MSGF_USER;
    msg.lParam = (LPARAM)this;
    DispatchMessage(&msg);

    SYSTEMTIME time;
    GetLocalTime(&time);
    double second = time::ConvertTime(time);
    double second_temp = 0.0;
    double second_delta = 0.0;
    double second_sleep = 0.0;
    double second_per_frame_min = 1.0 / 60.0;

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
        GetLocalTime(&time);
        second_temp = second;
        second = time::ConvertTime(time);
        second_delta = second - second_temp;
        if (m_pRender->Render(static_cast<float>(second_delta), rpScene))
        {
          SwapBuffers(m_pDC);
        }

        GetLocalTime(&time);
        second_sleep = second_per_frame_min - (time::ConvertTime(time) - second);
        if (0.001 < second_sleep)
        {
          //printf("%d time: s-%f | temp-%f | delta-%f | spf-%f | sleep-%f\n", ++count, second, second_temp, second_delta, second_per_frame_min, second_sleep);
          Sleep(static_cast<DWORD>(second_sleep * 1000));
        }
      }
    }
#endif

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

void CDisplay::Handle(const display::CInput& roInput)
{
  if (NULL != m_pScene) m_pScene->Handle(&roInput);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if (NULL != CDisplay::instance_ptr)
  {
    switch (uMsg)
    {
    //case WM_ACTIVATE:

    case WM_CLOSE:
      PostQuitMessage(0);
      return 0;

    case WM_GETMINMAXINFO: {
      LPMINMAXINFO mm_info = (LPMINMAXINFO)lParam;
      mm_info->ptMinTrackSize.x = CDisplay::instance_ptr->MinWidth();
      mm_info->ptMinTrackSize.y = CDisplay::instance_ptr->MinHeight();
      } return 0;

    case WM_SIZE:
      CDisplay::instance_ptr->Resize(LOWORD(lParam), HIWORD(lParam));
      return 0;

    case WM_KEYDOWN: {
      display::CInput& input = CDisplay::instance_ptr->Input();
      input.type = EInputType_Key;
      input.event = EInputEvent_Down;
      (*input[C4G_INPUT_KEY_KEYCODE]) = static_cast<int>(wParam);
      CDisplay::instance_ptr->Handle(input);
      } return 0;

    case WM_KEYUP: {
      display::CInput& input = CDisplay::instance_ptr->Input();
      input.type = EInputType_Key;
      input.event = EInputEvent_Up;
      (*input[C4G_INPUT_KEY_KEYCODE]) = static_cast<int>(wParam);
      CDisplay::instance_ptr->Handle(input);
      } return 0;

    case WM_MOUSEMOVE: {
      display::CInput& input = CDisplay::instance_ptr->Input();
      input.type = EInputType_Touch;
      input.event = EInputEvent_Move;
      (*input[C4G_INPUT_TOUCH_COUNT]) = 1;
      (*input[C4G_INPUT_TOUCH_X]) = static_cast<float>(GET_X_LPARAM(lParam));
      (*input[C4G_INPUT_TOUCH_Y]) = static_cast<float>(GET_X_LPARAM(lParam));
      CDisplay::instance_ptr->Handle(input);
      } return 0;

    case WM_LBUTTONDOWN: {
      display::CInput& input = CDisplay::instance_ptr->Input();
      input.type = EInputType_Touch;
      input.event = EInputEvent_Down;
      (*input[C4G_INPUT_TOUCH_COUNT]) = 1;
      (*input[C4G_INPUT_TOUCH_X]) = static_cast<float>(GET_X_LPARAM(lParam));
      (*input[C4G_INPUT_TOUCH_Y]) = static_cast<float>(GET_X_LPARAM(lParam));
      CDisplay::instance_ptr->Handle(input);
      } return 0;

    case WM_LBUTTONUP: {
      display::CInput& input = CDisplay::instance_ptr->Input();
      input.type = EInputType_Touch;
      input.event = EInputEvent_Up;
      (*input[C4G_INPUT_TOUCH_COUNT]) = 1;
      (*input[C4G_INPUT_TOUCH_X]) = static_cast<float>(GET_X_LPARAM(lParam));
      (*input[C4G_INPUT_TOUCH_Y]) = static_cast<float>(GET_X_LPARAM(lParam));
      CDisplay::instance_ptr->Handle(input);
      } return 0;
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
  rect.right = m_iWidth;
  rect.top = 0;
  rect.bottom = m_iHeight;
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

display::CInput& CDisplay::Input()
{
  return m_oInput;
}

}
}
}

bool CreateModule(c4g::core::IModule*& rpDisplay)
{
  assert(rpDisplay == NULL);
  rpDisplay = new c4g::display::windows_gles::CDisplay();
  return true;
}

bool DestroyModule(c4g::core::IModule*& rpDisplay)
{
  assert(rpDisplay != NULL);
  delete rpDisplay;
  rpDisplay = NULL;
  return true;
}

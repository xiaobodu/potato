#pragma once

#include "common.h"

#include "display.h"
#include "input.h"

#include <Windows.h>

namespace c4g {
namespace core {
class IRender;
class IScene;
}
namespace utility{
class CSharedLibraryManager;
}

namespace display {
namespace windows_gles {

class CDisplay: public core::IDisplay
{
public:
  explicit CDisplay(const base::Config& roConfig);
  virtual ~CDisplay();

public:
  virtual void Run(core::IScene* const& rpScene);

public:
  void Resize(const int& riWidth, const int& riHeight);

protected:
  bool CreateOsWindow();
  void DestroyOsWindow();

private:
  HGLRC m_pRC;
  HDC m_pDC;
  HWND m_pWnd;
  HINSTANCE m_pInstance;
  bool m_bIsRunning;

  std::string m_sTitle;
  int m_iWidth;
  int m_iHeight;

  base::Config          m_oConfigRender;
  core::IRender*        m_pRender;
  utility::CSharedLibraryManager* m_pLibraryManager;

  core::IScene*         m_pScene;
  display::CInput       m_oInput;
};

}
}
}

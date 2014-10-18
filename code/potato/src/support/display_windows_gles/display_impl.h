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
  static CDisplay* instance_ptr;

public:
  explicit CDisplay();
  virtual ~CDisplay();

public:
  virtual bool Initialize(core::MString2Module& rmModule);

public:
  virtual void Run(core::IScene* const& rpScene);

public:
  inline const int& MinWidth() const { return m_iMinWidth; }
  inline const int& MinHeight() const { return m_iMinHeight; }
  inline const int& Width() const { return m_iWidth; }
  inline const int& Height() const { return m_iHeight; }
  void Resize(const int& riWidth, const int& riHeight);
  void Handle(const display::CInput& roInput);

protected:
  bool CreateOsWindow();
  void DestroyOsWindow();

public:
  display::CInput& Input();

private:
  HGLRC m_pRC;
  HDC m_pDC;
  HWND m_pWnd;
  HINSTANCE m_pInstance;
  bool m_bIsRunning;

  std::string m_sTitle;
  int m_iMinWidth;
  int m_iMinHeight;
  int m_iWidth;
  int m_iHeight;

  core::IRender*        m_pRender;

  core::IScene*         m_pScene;
  display::CInput       m_oInput;
};

}
}
}

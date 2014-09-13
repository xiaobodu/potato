#pragma once

#include "common.h"

#include "display.h"
#include "input.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <EGL/egl.h>

namespace c4g {
namespace core {
class IRender;
class IScene;
}
namespace utility{
class CSharedLibraryManager;
}

namespace display {
namespace linux_gles {

class CDisplay: public core::IDisplay
{
public:
  explicit CDisplay(const base::Config& roConfig);
  virtual ~CDisplay();

public:
  virtual void Run(core::IScene* const& rpScene);

protected:
  void CreateWindow();
  void DestroyWindow();

private:
  Display* m_pDisplay;
  Window m_lWindow;
  Atom m_lProtocolsDeleteWindow;

  EGLConfig m_pGLConfig;
  EGLDisplay m_pGLDisplay;
  EGLContext m_pGLContext;
  EGLSurface m_pGLSurface;

  bool m_bIsRunning;

  std::string m_sTitle;
  int m_iWidth;
  int m_iHeight;

  base::Config          m_oConfigRender;
  core::IRender*        m_pRender;
  utility::CSharedLibraryManager* m_pLibraryManager;

  display::CInput       m_oInput;
};

}
}
}

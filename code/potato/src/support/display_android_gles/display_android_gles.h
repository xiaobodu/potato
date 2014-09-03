#pragma once

#include "common.h"

#include "display.h"

#include <EGL/egl.h>

namespace ac {
namespace display {

class CDisplay: public core::IDisplay
{
public:
  CDisplay(const ac::base::Config& roConfig);
  virtual ~CDisplay();

public:
  virtual void BindRender(core::IRender*& rpRender);
  virtual void Run();

protected:
  void Initialize(EGLNativeWindowType pWindow);

private:
  EGLDisplay m_pGLDisplay;
  EGLSurface m_pGLSurface;
  EGLContext m_pGLContext;
  EGLConfig m_pGLConfig;

  bool m_bIsRunning;

  core::IRender* m_pRender;
};

}
}

FUNC_API_DECLARE(CreateDisplay, ac::core::IDisplay, const ac::base::Config);
FUNC_API_DECLARE(DestroyDisplay, ac::core::IDisplay, const ac::base::Config);

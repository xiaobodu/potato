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
  virtual void Run(android_app* pApp);

public:
  void Initialize(android_app* pApp);
  void Stop();
  void Continue();
  void Pause();

private:
  EGLDisplay m_pGLDisplay;
  EGLSurface m_pGLSurface;
  EGLContext m_pGLContext;
  EGLConfig m_pGLConfig;

  bool m_bIsRunning;
  bool m_bIsEGLReady;
  bool m_bCanRender;

  core::IRender* m_pRender;
};

}
}

FUNC_API_DECLARE(CreateDisplay, ac::core::IDisplay, const ac::base::Config);
FUNC_API_DECLARE(DestroyDisplay, ac::core::IDisplay, const ac::base::Config);

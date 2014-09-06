#pragma once

#include "common.h"

#include "display.h"

#include <EGL/egl.h>

namespace c4g {

namespace utility{
class DynamicLibraryManager;
}

namespace display {
namespace android_gles {

class CDisplay: public core::IDisplay
{
public:
  CDisplay(const base::Config& roConfig);
  virtual ~CDisplay();

public:
  virtual void BindAndroidApp(struct android_app* pApp);
  virtual void Run();

public:
  void Initialize(android_app* pApp);
  void Terminated();
  void Continue();
  void Pause();
  void Stop();
  void Resize(const int& riWidth, const int& riHeight);

private:
  EGLDisplay    m_pGLDisplay;
  EGLSurface    m_pGLSurface;
  EGLContext    m_pGLContext;
  EGLConfig     m_pGLConfig;

  bool          m_bIsInitialized;
  bool          m_bIsRunning;
  bool          m_bIsEGLReady;
  bool          m_bCanRender;

  base::Config          m_oConfigRender;
  core::IRender*        m_pRender;
  utility::DynamicLibraryManager* m_pLibraryManager;

  // android
  struct android_app*           m_pApp;
  const struct ASensor*         m_pAccelerometerSensor;
  struct ASensorEventQueue*     m_pAccelerometerSensorEventQueue;
};

}
}
}

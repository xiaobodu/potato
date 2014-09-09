#pragma once

#include "common.h"

#include "display.h"

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
namespace android_gles {

class CDisplay: public core::IDisplay
{
public:
  explicit CDisplay(const base::Config& roConfig);
  virtual ~CDisplay();

public:
  virtual void BindAndroidApp(struct android_app* pApp);
  virtual void Run(core::IScene* const& rpScene);

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
  core::IScene*         m_pScene;
  utility::CSharedLibraryManager* m_pLibraryManager;

  // android
  struct android_app*           m_pApp;
  struct ASensorManager*        m_pSensorManager;
  const struct ASensor*         m_pAccelerometerSensor;
  struct ASensorEventQueue*     m_pAccelerometerSensorEventQueue;
};

}
}
}

#pragma once

#include "common.h"

#if defined(BUILD_ANDROID)
#include <EGL/egl.h>
#endif

namespace ac{
namespace core{

class IRender;

class IDisplay
{
public:
  virtual ~IDisplay() { ; }

public:
  virtual void BindRender(IRender*& rpRender) = 0;
#if defined(BUILD_ANDROID)
  virtual void BindAndroidApp(struct android_app* pApp) = 0;
#endif
  virtual void Run() = 0;
};

} // end of namespace core

namespace display{

class IInput
{
public:
  virtual ~IInput() { ; }
};

} // end of namespace display
} // end of namespace ac

FUNC_API_DECLARE(CreateDisplay, ac::core::IDisplay, const ac::base::Config);
FUNC_API_DECLARE(DestroyDisplay, ac::core::IDisplay, const ac::base::Config);

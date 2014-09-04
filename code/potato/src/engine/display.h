#pragma once

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
  virtual void Run(struct android_app* pApp) = 0;
#else
  virtual void Run() = 0;
#endif
};

} // end of namespace core

namespace display{



} // end of namespace display
} // end of namespace ac

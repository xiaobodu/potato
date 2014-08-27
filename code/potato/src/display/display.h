#pragma once

#include <X11/Xlib.h>

namespace ac{
namespace core{

class IRender;

class IDisplay
{
public:
  virtual ~IDisplay() { ; }

public:
  virtual void BindRender(IRender*& rpRender) = 0;
  virtual void Run() = 0;
};

} // end of namespace core

namespace display{



} // end of namespace display
} // end of namespace ac

#pragma once

#include "common.h"

#include "render/render.h"

namespace ac{
namespace core{

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

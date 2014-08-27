#pragma once

namespace ac{
namespace core{

class IDisplay;

class IRender
{
public:
  virtual ~IRender() { ; }

public:
  virtual void Start() = 0;
  virtual bool Tick(const double& rdDeltaS) = 0;
  virtual void Resize(int iWidth, int iHeight) = 0;
  virtual void End() = 0;
};

}

namespace render{

}
}

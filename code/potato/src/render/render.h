#pragma once

namespace ac{
namespace core{

class IRender
{
public:
  virtual ~IRender() { ; }

public:
  virtual void Start() = 0;
  virtual bool Tick(const double& rdDeltaS) = 0;
  virtual void End() = 0;
  virtual void Resize(const int& riWidth, const int& riHeight) = 0;
};

}

namespace render{

}
}

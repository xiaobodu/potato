#pragma once

#include "base.h"

#define MODULE_TYPE_FLASH    "flash"

namespace c4g {

namespace render {
class ITransform;
class IBlend;
}

namespace flash {
class IEffect;
}

namespace core {

class C4G_API IFlash : public IModule
{
public:
  explicit IFlash()
    : IModule(MODULE_TYPE_FLASH)
  {
    ;
  }
  virtual ~IFlash() { ; }

public:
  virtual flash::IEffect* New(const std::string& rsName) const = 0;
  virtual void Load(const std::string& rsFullFileName) = 0;
};

}

namespace flash {

class IEffect
{
public:
  virtual ~IEffect() { ; }

public:
  virtual IEffect* New() const = 0;

public:
  virtual void Play() = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Continue() = 0;
  virtual void Resize(const float& rfWidth, const float& rfHeight, const float& rfDepth) = 0;
  virtual bool Tick(const float& rfDelta) = 0;
  virtual void PreMake() = 0;
  virtual bool Make(render::ITransform* const& rpTransform) { return false; }
  virtual bool Make(render::IBlend* const& rpBlend) { return false; }
  virtual void PostMake() = 0;
};


}
}

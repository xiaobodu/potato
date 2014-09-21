#pragma once

#include "common.h"

#include "base.h"

namespace c4g {

namespace render {
class ITransform;
class IBlend;
}

namespace flash {
class IEffect;
}

namespace core {

class IFlash
{
public:
  virtual ~IFlash() { ; }

public:
  virtual flash::IEffect* New(const std::string& rsName) const = 0;
  virtual void Load(const std::string& rsFileName) = 0;
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

FUNC_API_DECLARE(CreateFlash, c4g::core::IFlash, const c4g::base::Config);
FUNC_API_DECLARE(DestroyFlash, c4g::core::IFlash, const c4g::base::Config);

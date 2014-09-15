#pragma once

#include "common.h"

#include "base.h"

namespace c4g {

namespace render {
class ITransform;
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
};

}

namespace flash {

class IEffect
{
public:
  virtual ~IEffect() { ; }

public:
  virtual void Play() = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Continue() = 0;
  virtual bool Tick(const float& rfDelta) = 0;
  virtual void Make(render::ITransform* const& rpTransform) = 0;
};


}
}

FUNC_API_DECLARE(CreateFlash, c4g::core::IFlash, const c4g::base::Config);
FUNC_API_DECLARE(DestroyFlash, c4g::core::IFlash, const c4g::base::Config);

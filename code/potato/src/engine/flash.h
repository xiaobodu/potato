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
};

}

namespace flash {

class IEffect
{
public:
  virtual ~IEffect() { ; }

public:
  virtual bool IsCustom() const { return false; }
  virtual void Begin() = 0;
  virtual void Begin(const base::Glyph& rGlyph) = 0;
  virtual bool Do(render::ITransform* const& rpTransform) = 0;
  virtual void End() = 0;
};

inline bool IsEffectCustom(IEffect* const& rpProcess)
{
  return ((NULL == rpProcess) ? false : rpProcess->IsCustom());
}

}
}

FUNC_API_DECLARE(CreateFlash, c4g::core::IFlash, const c4g::base::Config);
FUNC_API_DECLARE(DestroyFlash, c4g::core::IFlash, const c4g::base::Config);

#pragma once

#include "render.h"

namespace c4g {
namespace scene {

class CEffect : public render::IEffect
{
public:
  CEffect();
  virtual ~CEffect();

public:
  void SetPos(const float& rfX, const float& rfY);

public:
  virtual void Begin();
  virtual void Begin(const render::Glyph& rGlyph);
  virtual bool Do(render::ITransform* const& rpTransform);
  virtual void End();

public:
  bool Tick(const float& rfDelta);

private:
  float m_fX;
  float m_fY;
  float m_fAngle;
};

}
}

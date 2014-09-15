#pragma once

#include "flash.h"

namespace c4g {
namespace flash {

class CEffectRotate : public IEffect
{
public:
  CEffectRotate();
  virtual ~CEffectRotate();

public:
  virtual void Play();
  virtual void Stop();
  virtual void Pause();
  virtual void Continue();
  virtual bool Tick(const float& rfDelta);
  virtual void Make(render::ITransform* const& rpTransform);

private:
  bool m_bPlaying;
  float m_fTime;
  float m_fAngle;
};

}
}

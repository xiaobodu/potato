#pragma once

#include <rapidjson/document.h>

#include "flash.h"

namespace c4g {
namespace flash {

class CEffectRotate : public IEffect
{
public:
  static CEffectRotate instance;

public:
  float speed;

public:
  CEffectRotate();
  virtual ~CEffectRotate();

public:
  virtual IEffect* New() const;

public:
  virtual void Play();
  virtual void Stop();
  virtual void Pause();
  virtual void Continue();
  virtual void Resize(const float& rfWidth, const float& rfHeight, const float& rfDepth);
  virtual bool Tick(const float& rfDelta);
  virtual void PreMake();
  virtual bool Make(render::ITransform* const& rpTransform);
  virtual void PostMake();

private:
  bool m_bPlaying;
  float m_fTime;
  float m_fAngle;
  float m_fWidth;
  float m_fHeight;
  float m_fDepth;

public:
  void Build(const rapidjson::Value& roConfig);
};

}
}

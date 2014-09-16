#pragma once

#include <rapidjson/document.h>

#include "flash_base.h"

namespace c4g {
namespace flash {

class CEffectRotate : public IEffect
{
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

public:
  void Build(const rapidjson::Value& roConfig);
};

class CEffectTypeRotate : public IEffectType
{
  friend class CFlash;

private:
  static std::string name;

private:
  CEffectTypeRotate();
  virtual ~CEffectTypeRotate();

public:
  virtual IEffect* New(const rapidjson::Value& roConfig) const;
};

}
}

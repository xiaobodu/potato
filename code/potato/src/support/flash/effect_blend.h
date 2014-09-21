#pragma once

#include <rapidjson/document.h>

#include "flash_base.h"

namespace c4g {
namespace flash {

class CEffectBlend : public IEffect
{
public:
  base::SColor color;
  base::Color::Flags flags;

public:
  CEffectBlend();
  virtual ~CEffectBlend();

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
  virtual bool Make(render::IBlend* const& rpBlend);
  virtual void PostMake();

private:
  bool m_bPlaying;
  bool m_bPause;
  float m_fTime;

public:
  void Build(const rapidjson::Value& roConfig);
};

class CEffectTypeBlend : public IEffectType
{
  friend class CFlash;

private:
  static std::string name;

private:
  CEffectTypeBlend();
  virtual ~CEffectTypeBlend();

public:
  virtual IEffect* New(const rapidjson::Value& roConfig) const;
};

}
}

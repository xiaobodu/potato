#pragma once

#include "flash.h"

#include <map>

namespace c4g {
namespace flash {

class IEffectType;

class CFlash : public core::IFlash
{
public:
  CFlash(const c4g::base::Config& roConfig);
  virtual ~CFlash();

public:
  virtual IEffect* New(const std::string& rsId) const;
  virtual void Load(const std::string& rsFileName);

protected:
  void Push(const std::string& rsId, flash::IEffect* const& rpEffect);
  void PushType(const std::string& rsType, flash::IEffectType* const& rpEffect);
  const flash::IEffectType* const GetType(const std::string& rsName) const;

private:
  typedef std::map<std::string, IEffect* const> MEffects;
  MEffects m_mEffect;
  typedef std::map<std::string, IEffectType* const> MEffectTypes;
  MEffectTypes m_mEffectType;
};

}
}

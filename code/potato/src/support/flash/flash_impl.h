#pragma once

#include "flash.h"

#include <map>

namespace c4g {
namespace flash {

class CFlash : public core::IFlash
{
public:
  CFlash(const c4g::base::Config& roConfig);
  virtual ~CFlash();

public:
  virtual IEffect* New(const std::string& rsName) const;
  virtual void Load(const std::string& rsName);

protected:
  void Push(const std::string& rsName, flash::IEffect* const& rpEffect);
  void PushTemplate(const std::string& rsName, flash::IEffect* const& rpEffect);

private:
  typedef std::map<std::string, IEffect* const> MEffects;
  MEffects m_mEffect;
  MEffects m_mEffectTemplate;
};

}
}

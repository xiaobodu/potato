#pragma once

#include <rapidjson/document.h>

#include "flash.h"

namespace c4g {
namespace flash {

class IEffectType
{
public:
  virtual ~IEffectType()
  {
    ;
  }

public:
  virtual IEffect* New(const rapidjson::Value& roConfig) const = 0;
};

}
}

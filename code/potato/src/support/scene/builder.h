#pragma once

#include <string>
#include <rapidjson/document.h>

namespace c4g {

namespace core {
class IAsset;
}

namespace scene {

template<typename TGoods>
class TBuilder
{
public:
  const std::string name;

public:
  explicit TBuilder(const std::string& rsName)
    : name(rsName)
  {
    ;
  }
  virtual ~TBuilder()
  {
    ;
  }

public:
  virtual bool Parser(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, TGoods& rGoods) const = 0;
};

}
}

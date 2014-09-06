#pragma once

#include "asset.h"

namespace c4g{

namespace core{
class IAsset;
}

namespace asset{

class CAsset : public core::IAsset
{
public:
  explicit CAsset(const c4g::base::Config& roConfig);
  virtual ~CAsset();

public:
  virtual void Load(const std::string& rsFileName);
};

}

}

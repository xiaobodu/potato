#pragma once

#include "asset.h"

namespace ac{

namespace core{
class IAsset;
}

namespace asset{

class CAsset : public core::IAsset
{
public:
  explicit CAsset(const ac::base::Config& roConfig);
  virtual ~CAsset();

public:
  virtual void Load(const std::string& rsFileName);
};

}

}

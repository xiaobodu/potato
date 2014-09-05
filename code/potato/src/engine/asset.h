#pragma once

#include "common.h"

namespace ac{
namespace core{

class IAsset
{
public:
  virtual ~IAsset() { ; }

public:
  virtual void Load(const std::string& rsFileName) = 0;
};

}
}

FUNC_API_DECLARE(CreateAsset, ac::core::IAsset, const ac::base::Config);
FUNC_API_DECLARE(DestroyAsset, ac::core::IAsset, const ac::base::Config);

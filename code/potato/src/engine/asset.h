#pragma once

#include "common.h"

namespace c4g {
namespace core {

class IAsset
{
public:
  virtual ~IAsset()
  {
    ;
  }

public:
  virtual void LoadImage(const std::string& rsFileName, int& riWidth, int& riHeight, unsigned char*& rpBuffer) = 0;
};

}
}

FUNC_API_DECLARE(CreateAsset, c4g::core::IAsset, const c4g::base::Config);
FUNC_API_DECLARE(DestroyAsset, c4g::core::IAsset, const c4g::base::Config);

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
  virtual void LoadFile(const std::string& rsFileName, std::string& rsFileContext) = 0;
  virtual void LoadImage(const std::string& rsFileName, int& riWidth, int& riHeight, unsigned char*& rpBuffer) = 0;
  virtual void PushImageInfo(const std::string& rsId, const int& riWidth, const int& riHeight, const int& riId) = 0;
  virtual bool FindImageInfo(const std::string& rsId, int& riWidth, int& riHeight, int& riId) const = 0;
};

}
}

FUNC_API_DECLARE(CreateAsset, c4g::core::IAsset, const c4g::base::Config);
FUNC_API_DECLARE(DestroyAsset, c4g::core::IAsset, const c4g::base::Config);

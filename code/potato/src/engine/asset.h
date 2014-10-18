#pragma once

#include "base.h"

#define MODULE_TYPE_ASSET    "asset"

namespace c4g {
namespace core {

class C4G_API IAsset : public IModule
{
public:
  explicit IAsset()
    : IModule(MODULE_TYPE_ASSET)
  {
    ;
  }
  virtual ~IAsset()
  {
    ;
  }

public:
  virtual void LoadFile(const std::string& rsFileName, std::string& rsFileContext) = 0;
  virtual void LoadImagePNG(const std::string& rsFileName, int& riWidth, int& riHeight, unsigned char*& rpBuffer) = 0;
  virtual void PushImageInfo(const std::string& rsId, const int& riWidth, const int& riHeight, const unsigned int& riId) = 0;
  virtual bool FindImageInfo(const std::string& rsId, int& riWidth, int& riHeight, unsigned int& riId) const = 0;

public:
  class IImageInfoVisitor
  {
  public:
    virtual void On(const std::string& rsId, const int& riWidth, const int& riHeight, const unsigned int& riId) const = 0;
  };
  virtual void VisitImageInfo(IImageInfoVisitor* const& rpVisitor) const = 0;
  virtual void ClearImageInfo() = 0;
};

}
}

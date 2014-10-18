#pragma once

#include "asset.h"

#include "base.h"

#include <string>
#include <map>

namespace c4g{

namespace core{
class IAsset;
}

namespace asset{

class CAsset : public core::IAsset
{
public:
  explicit CAsset();
  virtual ~CAsset();

public:
  virtual bool Initialize(core::MString2Module& rmModule);

public:
  virtual void LoadFile(const std::string& rsFullFileName, std::string& rsFileContext);
  virtual void LoadImagePNG(const std::string& rsFullFileName, int& riWidth, int& riHeight, unsigned char*& rpBuffer);
  virtual void PushImageInfo(const std::string& rsId, const int& riWidth, const int& riHeight, const unsigned int& riId);
  virtual bool FindImageInfo(const std::string& rsId, int& riWidth, int& riHeight, unsigned int& riId) const;
  virtual void VisitImageInfo(core::IAsset::IImageInfoVisitor* const& rpVisitor) const;
  virtual void ClearImageInfo();

private:
  struct ImageInfo
  {
    int width;
    int height;
    unsigned int id;

    ImageInfo() : width(0), height(0), id(0) { ; }
  };
  typedef std::map<std::string, ImageInfo>   MImageInfo;
  MImageInfo  m_mImageInfo;
};

}

}

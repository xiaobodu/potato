#pragma once

#include "asset.h"

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
  explicit CAsset(const c4g::base::Config& roConfig);
  virtual ~CAsset();

private:
  c4g::base::Config m_oConfig;

public:
  virtual void LoadFile(const std::string& rsFileName, std::string& rsFileContext);
  virtual void LoadImage(const std::string& rsFileName, int& riWidth, int& riHeight, unsigned char*& rpBuffer);
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

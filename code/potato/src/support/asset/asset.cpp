#include "asset_impl.h"

#include "file_png.h"
#include "utility/log.h"
#include "utility/file.h"

#include <cassert>

namespace c4g{

namespace asset{

CAsset::CAsset(const c4g::base::Config& roConfig)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_oConfig = roConfig;
}

CAsset::~CAsset()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

void CAsset::LoadFile(const std::string& rsFileName, std::string& rsFileContext, bool bIsAbsolutePath /*= false*/)
{
  if (bIsAbsolutePath) rsFileContext = utility::ReadFile(rsFileName);
  else rsFileContext = utility::ReadFile(m_oConfig._sDataPath + "/" + rsFileName);
}

void CAsset::LoadImage(const std::string& rsFileName, int& riWidth, int& riHeight, unsigned char*& rpBuffer, bool bIsAbsolutePath /*= false*/)
{
  if (bIsAbsolutePath) CFilePNG::Instance().Load(rsFileName);
  else CFilePNG::Instance().Load(m_oConfig._sDataPath + "/" + rsFileName);

  riWidth = static_cast<int>(CFilePNG::Instance().GetWidth());
  riHeight = static_cast<int>(CFilePNG::Instance().GetHeight());
  rpBuffer = static_cast<unsigned char*>(CFilePNG::Instance().GetBuffer());
}

void CAsset::PushImageInfo(const std::string& rsId, const int& riWidth, const int& riHeight, const unsigned int& riId)
{
  if (0 >= riId) return;
  ImageInfo info;
  info.width = riWidth;
  info.height = riHeight;
  info.id = riId;
  m_mImageInfo.insert(std::make_pair(rsId, info));
}

bool CAsset::FindImageInfo(const std::string& rsId, int& riWidth, int& riHeight, unsigned int& riId) const
{
  MImageInfo::const_iterator cit_find = m_mImageInfo.find(rsId);
  if (cit_find == m_mImageInfo.end()) return false;
  const ImageInfo& info_ref = cit_find->second;
  riWidth = info_ref.width;
  riHeight = info_ref.height;
  riId = info_ref.id;
  return true;
}

void CAsset::VisitImageInfo(core::IAsset::IImageInfoVisitor* const& rpVisitor) const
{
  MImageInfo::const_iterator cit = m_mImageInfo.begin();
  MImageInfo::const_iterator cit_end = m_mImageInfo.end();
  for (; cit != cit_end; ++cit)
  {
    const ImageInfo& info_ref = (*cit).second;
    rpVisitor->On((*cit).first, info_ref.width, info_ref.height, info_ref.id);
  }
}

void CAsset::ClearImageInfo()
{
  if (m_mImageInfo.empty()) return;
  m_mImageInfo.clear();
}

}

}


bool CreateAsset(c4g::core::IAsset*& rpAsset, const c4g::base::Config& roConfig)
{
  assert(rpAsset == NULL);
  if (rpAsset != NULL)
  {
    return false;
  }
  rpAsset = new c4g::asset::CAsset(roConfig);
  return true;
}

bool DestroyAsset(c4g::core::IAsset*& rpAsset, const c4g::base::Config& roConfig)
{
  assert(rpAsset != NULL);
  if (NULL == rpAsset)
  {
    return false;
  }
  delete rpAsset;
  rpAsset = NULL;
  return true;
}

#include "asset_impl.h"

#include "file_png.h"
#include "utility/log.h"
#include "utility/file.h"

#include <cassert>

namespace c4g{

namespace asset{

CAsset::CAsset()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

CAsset::~CAsset()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

bool CAsset::Initialize(core::MString2Module& rmModule)
{
  return true;
}

void CAsset::LoadFile(const std::string& rsFullFileName, std::string& rsFileContext)
{
  rsFileContext = utility::ReadFile(rsFullFileName);
}

void CAsset::LoadImage(const std::string& rsFullFileName, int& riWidth, int& riHeight, unsigned char*& rpBuffer)
{
  //TODO:
  CFilePNG::Instance().Load(rsFullFileName);

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


bool CreateModule(c4g::core::IModule*& rpAsset)
{
  assert(rpAsset == NULL);
  if (rpAsset != NULL)
  {
    return false;
  }
  rpAsset = new c4g::asset::CAsset();
  return true;
}

bool DestroyModule(c4g::core::IModule*& rpAsset)
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

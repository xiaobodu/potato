#include "asset_impl.h"

#include "file_png.h"
#include "utility/log.h"

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

void CAsset::LoadImage(const std::string& rsFileName, int& riWidth, int& riHeight, unsigned char*& rpBuffer)
{
  CFilePNG::Instance().Load(m_oConfig._sDataPath + "/" + rsFileName);
  riWidth = static_cast<int>(CFilePNG::Instance().GetWidth());
  riHeight = static_cast<int>(CFilePNG::Instance().GetHeight());
  rpBuffer = static_cast<unsigned char*>(CFilePNG::Instance().GetBuffer());
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

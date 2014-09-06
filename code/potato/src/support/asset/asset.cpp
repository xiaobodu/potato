#include "asset_impl.h"

#include <cassert>

namespace c4g{

namespace asset{

CAsset::CAsset(const c4g::base::Config& roConfig)
{
  ;
}

CAsset::~CAsset()
{
  ;
}

void CAsset::Load(const std::string& rsFileName)
{
  ;
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

#include "asset_impl.h"

#include <cassert>

namespace ac{

namespace asset{

CAsset::CAsset(const ac::base::Config& roConfig)
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


bool CreateAsset(ac::core::IAsset*& rpAsset, const ac::base::Config& roConfig)
{
  assert(rpAsset == NULL);
  if (rpAsset != NULL)
  {
    return false;
  }
  rpAsset = new ac::asset::CAsset(roConfig);
  return true;
}

bool DestroyAsset(ac::core::IAsset*& rpAsset, const ac::base::Config& roConfig)
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

#include "asset.h"

#include <cassert>

bool CreateAsset(ac::core::IAsset*& rpAsset, const ac::base::Config& roConfig)
{
  assert(rpAsset == NULL);
  if (rpAsset != NULL)
  {
    return false;
  }
  //rpAsset = new ac::display::CAsset(roConfig);
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

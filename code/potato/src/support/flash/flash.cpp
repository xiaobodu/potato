#include "flash_impl.h"

#include <cassert>

namespace c4g {
namespace flash {

CFlash::CFlash(const c4g::base::Config& roConfig)
{
  ;
}

CFlash::~CFlash()
{
  ;
}

}
}


bool CreateFlash(c4g::core::IFlash*& rpFlash, const c4g::base::Config& roConfig)
{
  assert(rpFlash == NULL);
  if (rpFlash != NULL)
  {
    return false;
  }
  rpFlash = new c4g::flash::CFlash(roConfig);
  return true;
}

bool DestroyFlash(c4g::core::IFlash*& rpFlash, const c4g::base::Config& roConfig)
{
  assert(rpFlash != NULL);
  if (NULL == rpFlash)
  {
    return false;
  }
  delete rpFlash;
  rpFlash = NULL;
  return true;
}

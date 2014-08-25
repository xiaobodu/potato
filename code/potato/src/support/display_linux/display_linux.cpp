#include <cassert>

#include "display_linux.h"

namespace ac{
namespace core{

CDisplay::CDisplay(const ac::base::Config& roConfig)
{
  ;
}

CDisplay::~CDisplay()
{
  ;
}

}
}

bool CreateDisplay(ac::core::IDisplay*& rpDisplay, const ac::base::Config& roConfig)
{
  assert(rpDisplay == NULL);
  rpDisplay = new ac::core::CDisplay(roConfig);
  return true;
}

bool DestroyDisplay(ac::core::IDisplay*& rpDisplay, const ac::base::Config& roConfig)
{
  assert(rpDisplay != NULL);
  delete rpDisplay;
  rpDisplay = NULL;
  return true;
}

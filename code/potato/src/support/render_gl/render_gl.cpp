#include <cassert>

#include "render_gl.h"

namespace ac{
namespace core{

CRender::CRender(const base::Config& roConfig)
{
  ;
}

CRender::~CRender()
{
  ;
}

}
}

bool CreateRender(ac::core::IRender*& rpRender, const ac::base::Config& roConfig)
{
  assert(rpRender == NULL);
  rpRender = new ac::core::CRender(roConfig);
  return true;
}

bool DestroyRender(ac::core::IRender*& rpRender, const ac::base::Config& roConfig)
{
  assert(rpRender != NULL);
  delete rpRender;
  rpRender = NULL;
  return true;
}

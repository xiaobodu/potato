#include "space.h"

#include <cassert>

namespace c4g{
namespace render {
namespace gles {

CSpace::CSpace(ICamera* const pCamera)
  : m_pCamera(pCamera)
{
  assert(!!pCamera);
  ;
}

CSpace::~CSpace()
{
  ;
}

void CSpace::EffectBegin(IProcess* const& rpProcess)
{
  //TODO:
}

void CSpace::EffectEnd(IProcess* const& rpProcess)
{
  //TODO:
}

void CSpace::DrawModel(const base::Model& rModel, IProcess* const& rpProcess /*= NULL*/)
{
  //TODO:
}

}
}
}

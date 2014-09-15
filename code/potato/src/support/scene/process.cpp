#include "process.h"

namespace c4g {
namespace scene {

CProcess::CProcess()
  : m_fX(0.0f), m_fY(0.0f)
{
  ;
}
CProcess::~CProcess()
{
  ;
}

void CProcess::SetPos(const float& rfX, const float& rfY)
{
  m_fX = rfX;
  m_fY = rfY;
}

bool CProcess::Do(render::ITransform* const & rpTransform)
{
  rpTransform->Translate(m_fX, m_fY);
  return true;
}

}
}

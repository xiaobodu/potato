#include "effect.h"

namespace c4g {
namespace scene {

CEffect::CEffect()
    : m_fX(0.0f), m_fY(0.0f), m_fAngle(0.0f)
{
  ;
}
CEffect::~CEffect()
{
  ;
}

void CEffect::SetPos(const float& rfX, const float& rfY)
{
  m_fX = rfX;
  m_fY = rfY;
}

void CEffect::Begin()
{
  ;
}

void CEffect::Begin(const base::Glyph& rGlyph)
{
  ;
}

bool CEffect::Do(render::ITransform* const & rpTransform)
{
  // think in the 3d transform
  rpTransform->Translate(m_fX, m_fY);
  rpTransform->Rotate(m_fAngle, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
  return true;
}
void CEffect::End()
{
  ;
}

bool CEffect::Tick(const float& rfDelta)
{
  //m_fAngle += rfDelta * 200.0f;
  if (m_fAngle > 360.0f) m_fAngle -= 360.0f;
  return true;
}

}
}

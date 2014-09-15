#include "effect_rotate.h"

#include "render.h"

namespace c4g {
namespace flash {

CEffectRotate::CEffectRotate()
  : m_bPlaying(false)
  , m_fTime(0.0f)
  , m_fAngle(0.0f)
{
  ;
}

CEffectRotate::~CEffectRotate()
{
  ;
}

void CEffectRotate::Play()
{
  m_bPlaying = true;
}

void CEffectRotate::Stop()
{
  m_bPlaying = false;
}

void CEffectRotate::Pause()
{
  ;
}

void CEffectRotate::Continue()
{
  ;
}

bool CEffectRotate::Tick(const float& rfDelta)
{
  if (!m_bPlaying) return false;

  m_fTime += rfDelta;

  m_fAngle = m_fTime * 100.0f;

  if (360.0f < m_fAngle) m_fAngle -= 360.0f;
  //
  return true;
}

void CEffectRotate::Make(render::ITransform* const& rpTransform)
{
  rpTransform->Rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
}

}
}

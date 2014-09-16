#include "effect_rotate.h"

#include "render.h"

namespace c4g {
namespace flash {

CEffectRotate CEffectRotate::instance;

CEffectRotate::CEffectRotate()
  : speed(100.0f)
  , m_bPlaying(false)
  , m_fTime(0.0f)
  , m_fAngle(0.0f)
  , m_fWidth(0.0f)
  , m_fHeight(0.0f)
  , m_fDepth(0.0f)
{
  ;
}

CEffectRotate::~CEffectRotate()
{
  ;
}

IEffect* CEffectRotate::New() const
{
  CEffectRotate* res = new CEffectRotate();
  res->speed = speed;
  //TODO:
  return res;
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

void CEffectRotate::Resize(const float& rfWidth, const float& rfHeight, const float& rfDepth)
{
  m_fWidth = rfWidth;
  m_fHeight = rfHeight;
  m_fDepth = rfDepth;
}

bool CEffectRotate::Tick(const float& rfDelta)
{
  if (!m_bPlaying) return false;

  m_fTime += rfDelta;

  m_fAngle = m_fTime * speed;

  if (360.0f < m_fAngle) m_fAngle -= 360.0f;
  //
  return true;
}

void CEffectRotate::PreMake()
{
  ;
}

bool CEffectRotate::Make(render::ITransform* const& rpTransform)
{
  if (!m_bPlaying) return false;

  rpTransform->Rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
  return true;
}

void CEffectRotate::PostMake()
{
  ;
}

}
}

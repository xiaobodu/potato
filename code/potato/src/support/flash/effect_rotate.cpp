#include "effect_rotate.h"

#include "render.h"

#include "utility/log.h"

namespace c4g {
namespace flash {

std::string CEffectTypeRotate::name("rotate");

CEffectRotate::CEffectRotate()
  : speed(0.0f)
  , m_bPlaying(false)
  , m_fTime(0.0f)
  , m_fAngle(0.0f)
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
  ;
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

CEffectTypeRotate::CEffectTypeRotate()
{
  ;
}

CEffectTypeRotate::~CEffectTypeRotate()
{
  ;
}

IEffect* CEffectTypeRotate::New(const rapidjson::Value& roConfig) const
{
  const rapidjson::Value& jspeed = roConfig["speed"];
  assert(jspeed.IsDouble());
  if (!jspeed.IsDouble()) return NULL;

  CEffectRotate* res = new CEffectRotate();
  res->speed = static_cast<float>(jspeed.GetDouble());
  return res;
}

}
}

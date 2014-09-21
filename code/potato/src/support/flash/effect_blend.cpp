#include "effect_blend.h"

#include "render.h"

#include "utility/log.h"

namespace c4g {
namespace flash {

std::string CEffectTypeBlend::name("blend");

CEffectBlend::CEffectBlend()
  : flags(base::Color::eFlagBit_None)
  , m_bPlaying(false)
  , m_bPause(false)
  , m_fTime(0.0f)
{
  ;
}

CEffectBlend::~CEffectBlend()
{
  ;
}

IEffect* CEffectBlend::New() const
{
  CEffectBlend* res = new CEffectBlend();
  res->color = color;
  res->flags = flags;
  return res;
}

void CEffectBlend::Play()
{
  m_bPlaying = true;
  m_bPause = false;
}

void CEffectBlend::Stop()
{
  m_bPlaying = false;
}

void CEffectBlend::Pause()
{
  m_bPause = true;
}

void CEffectBlend::Continue()
{
  m_bPause = false;
}

void CEffectBlend::Resize(const float& rfWidth, const float& rfHeight, const float& rfDepth)
{
  ;
}

bool CEffectBlend::Tick(const float& rfDelta)
{
  if (!m_bPlaying) return false;

  if (!m_bPause)
  {
    m_fTime += rfDelta;

    color.a = static_cast<unsigned char>(m_fTime * 50.0f);

    if (m_fTime > 0xFF) m_fTime -= static_cast<float>(0xFF);
  }
  //
  return true;
}

void CEffectBlend::PreMake()
{
  ;
}

bool CEffectBlend::Make(render::IBlend* const& rpBlend)
{
  if (!m_bPlaying) return false;

  rpBlend->Multiply(color, flags);
  //
  return true;
}

void CEffectBlend::PostMake()
{
  ;
}

CEffectTypeBlend::CEffectTypeBlend()
{
  ;
}

CEffectTypeBlend::~CEffectTypeBlend()
{
  ;
}

IEffect* CEffectTypeBlend::New(const rapidjson::Value& roConfig) const
{
  base::SColor color;
  base::Color::Flags flags = base::Color::eFlagBit_None;

  if (roConfig.HasMember("r"))
  {
    const rapidjson::Value& jvalue = roConfig["r"];
    assert(jvalue.IsInt());
    if (jvalue.IsInt())
    {
      color.r = static_cast<unsigned char>(jvalue.GetInt());
      flags |= base::Color::eFlagBit_R;
    }
  }

  if (roConfig.HasMember("g"))
  {
    const rapidjson::Value& jvalue = roConfig["g"];
    assert(jvalue.IsInt());
    if (jvalue.IsInt())
    {
      color.g = static_cast<unsigned char>(jvalue.GetInt());
      flags |= base::Color::eFlagBit_G;
    }
  }

  if (roConfig.HasMember("b"))
  {
    const rapidjson::Value& jvalue = roConfig["b"];
    assert(jvalue.IsInt());
    if (jvalue.IsInt())
    {
      color.b = static_cast<unsigned char>(jvalue.GetInt());
      flags |= base::Color::eFlagBit_B;
    }
  }

  if (roConfig.HasMember("a"))
  {
    const rapidjson::Value& jvalue = roConfig["a"];
    assert(jvalue.IsInt());
    if (jvalue.IsInt())
    {
      color.a = static_cast<unsigned char>(jvalue.GetInt());
      flags |= base::Color::eFlagBit_A;
    }
  }

  CEffectBlend* res = new CEffectBlend();
  res->color = color;
  res->flags = flags;
  return res;
}

}
}

#include <rapidjson/document.h>

#include "flash_impl.h"

#include "effect_rotate.h"

#include "utility/file.h"
#include "utility/log.h"

#include <cassert>

namespace c4g {
namespace flash {

CFlash::CFlash(const c4g::base::Config& roConfig)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

#if defined(BUILD_ANDROID)
  std::string file_context = roConfig._sConfigureContext.c_str();
#else
  std::string file_context = utility::ReadFile(roConfig.GetConfigureFile());
#endif

  PushType("rotate", new CEffectTypeRotate);

  rapidjson::Document jdoc;
  jdoc.Parse(file_context.c_str());
  assert(jdoc.IsObject());

  const rapidjson::Value& jdata = jdoc["data"];
  if (jdata.IsString())
  {
    Load(roConfig._sDataPath + "/" + jdata.GetString());
  }
}

CFlash::~CFlash()
{
  {
    MEffects::iterator it = m_mEffect.begin();
    MEffects::iterator it_end = m_mEffect.end();
    for (; it != it_end; ++it)
    {
      IEffect* const& effect_ptr = (*it).second;
      delete effect_ptr;
    }
    m_mEffect.clear();
  }

  {
    MEffectTypes::iterator it = m_mEffectType.begin();
    MEffectTypes::iterator it_end = m_mEffectType.end();
    for (; it != it_end; ++it)
    {
      IEffectType* const& effecttype_ptr = (*it).second;
      delete effecttype_ptr;
    }
    m_mEffectType.clear();
  }

  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

void CFlash::Load(const std::string& rsFileName)
{
  std::string file_context = utility::ReadFile(rsFileName);

  rapidjson::Document jdoc;
  jdoc.Parse(file_context.c_str());
  assert(jdoc.IsObject());
  if (!jdoc.IsObject()) return;

  const rapidjson::Value& jeffects = jdoc["effects"];
  assert(jeffects.IsArray());
  if (!jeffects.IsArray()) return;

  for (int i = 0; i < static_cast<int>(jeffects.Size()); ++i)
  {
    const rapidjson::Value& jeffect = jeffects[i];
    assert(jeffect.IsObject());
    if (!jeffect.IsObject()) continue;
    const rapidjson::Value& jeffect_type = jeffect["type"];
    assert(jeffect_type.IsString());
    if (!jeffect_type.IsString()) continue;
    const rapidjson::Value& jeffect_id = jeffect["id"];
    assert(jeffect_id.IsString());
    if (!jeffect_id.IsString()) continue;
    const rapidjson::Value& jeffect_value = jeffect["value"];
    assert(jeffect_value.IsObject());
    if (!jeffect_value.IsObject()) continue;
    const flash::IEffectType* const effecttype_ptr = GetType(jeffect_type.GetString());
    if (NULL == effecttype_ptr) continue;
    std::string id = jeffect_id.GetString();
    IEffect* effect_ptr = effecttype_ptr->New(jeffect_value);
    if (NULL == effect_ptr) continue;
    Push(id, effect_ptr);
  }
}

IEffect* CFlash::New(const std::string& rsId) const
{
  MEffects::const_iterator cit_find = m_mEffect.find(rsId);
  if (cit_find == m_mEffect.end()) return NULL;

  IEffect* const& effect_ptr = (*cit_find).second;
  return effect_ptr->New();
}

void CFlash::Push(const std::string& rsId, flash::IEffect* const& rpEffect)
{
  if (NULL == rpEffect) return;

  m_mEffect.insert(std::make_pair(rsId, rpEffect));
}

void CFlash::PushType(const std::string& rsType, flash::IEffectType* const& rpEffectType)
{
  if (NULL == rpEffectType) return;

  m_mEffectType.insert(std::make_pair(rsType, rpEffectType));
}

const flash::IEffectType* const CFlash::GetType(const std::string& rsName) const
{
  MEffectTypes::const_iterator cit_find = m_mEffectType.find(rsName);
  if (cit_find == m_mEffectType.end()) return NULL;
  return (*cit_find).second;
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

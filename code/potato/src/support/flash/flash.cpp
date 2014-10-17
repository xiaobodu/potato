#include <rapidjson/document.h>

#include "flash_impl.h"

#include "effect_rotate.h"
#include "effect_blend.h"

#include "utility/file.h"
#include "utility/log.h"

#include <cassert>

namespace c4g {
namespace flash {

CFlash::CFlash()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  PushType(CEffectTypeRotate::name, new CEffectTypeRotate);
  PushType(CEffectTypeBlend::name, new CEffectTypeBlend);
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

bool CFlash::Initialize(core::MString2Module& rmModule)
{
  //TODO:
  return true;
}

void CFlash::Load(const std::string& rsFullFileName)
{
  std::string file_context = utility::ReadFile(rsFullFileName);

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


bool CreateModule(c4g::core::IModule*& rpFlash)
{
  assert(rpFlash == NULL);
  if (rpFlash != NULL)
  {
    return false;
  }
  rpFlash = new c4g::flash::CFlash();
  return true;
}

bool DestroyModule(c4g::core::IModule*& rpFlash)
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

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

  Push("rotate", &CEffectRotate::instance);

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
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

void CFlash::Load(const std::string& rsName)
{
  ;
}

IEffect* CFlash::New(const std::string& rsName) const
{
  MEffects::const_iterator cit_find = m_mEffect.find(rsName);
  if (cit_find == m_mEffect.end()) return NULL;

  IEffect* const& effect_ptr = (*cit_find).second;
  return effect_ptr->New();
}

void CFlash::Push(const std::string& rsName, flash::IEffect* const& rpEffect)
{
  if (NULL == rpEffect) return;

  m_mEffect.insert(std::make_pair(rsName, rpEffect));
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

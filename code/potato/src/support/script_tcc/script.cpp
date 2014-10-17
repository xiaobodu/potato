#include "script_impl.h"

#include "utility/log.h"

#include <cassert>
#if defined(__cplusplus)
extern "C" {
#endif
# include <libtcc.h>
#if defined(__cplusplus)
}
#endif

namespace c4g {
namespace script {

void log_info(char* txt)
{
  c4g::utility::Log::Instance().Info(txt);
}

void error_callback(void *opaque, const char *msg)
{
  c4g::utility::Log::Instance().Error(msg);
}

CScript::CScript()
{
  ;
}

CScript::~CScript()
{
  MSubstance::iterator it = m_mSubstance.begin();
  MSubstance::iterator it_end = m_mSubstance.end();
  for (; it != it_end; ++it)
  {
    script::AHandler* const& handler_ptr = (*it).first;
    delete (*it).second;
    handler_ptr->OnDeleteSubstance();
  }
  m_mSubstance.clear();
}

bool CScript::Initialize(core::MString2Module& rmModule)
{
  //TODO:
  return true;
}

void CScript::New(script::AHandler* const& rpHandler)
{
  if (NULL == rpHandler || rpHandler->HaveSubstance()) return;
  ISubstance* substance_ptr = new CSubstance();
  rpHandler->OnNewSubstance(this, substance_ptr);
  m_mSubstance.insert(std::make_pair(rpHandler, substance_ptr));
}

void CScript::Delete(script::AHandler* const& rpHandler)
{
  if (NULL == rpHandler) return;
  rpHandler->OnDeleteSubstance();
  MSubstance::iterator it_find = m_mSubstance.find(rpHandler);
  if (m_mSubstance.end() != it_find)
  {
    delete (*it_find).second;
    m_mSubstance.erase(it_find);
  }
}

CSubstance::CSubstance()
  : m_bCompiled(false)
{
  m_pTCC = tcc_new();
  if (NULL != m_pTCC)
  {
    tcc_set_output_type(m_pTCC, TCC_OUTPUT_MEMORY);
    tcc_set_error_func(m_pTCC, NULL, error_callback);

    // some common symbols
    tcc_add_symbol(m_pTCC, "log_info", (void const*)log_info);
  }
}

CSubstance::~CSubstance()
{
  if (NULL != m_pTCC)
  {
    tcc_delete(m_pTCC);
    m_pTCC = NULL;
  }
}

void CSubstance::Compile(const std::string& rsCode)
{
  if (m_bCompiled) return;

  m_bCompiled = (-1 != tcc_compile_string(m_pTCC, rsCode.c_str()));
  if (m_bCompiled)
  {
    m_bCompiled = (0 <= tcc_relocate(m_pTCC, TCC_RELOCATE_AUTO));
  }
}

bool CSubstance::SetSymbol(const std::string& rsFuncName, void* pFunc)
{
  if (!m_bCompiled) return false;

  return (0 <= tcc_add_symbol(m_pTCC, rsFuncName.c_str(), pFunc));
}

void* const CSubstance::GetSymbol(const std::string& rsFuncName)
{
  if (!m_bCompiled) return NULL;

  return tcc_get_symbol(m_pTCC, rsFuncName.c_str());
}

}
}

bool CreateModule(c4g::core::IModule*& rpScript)
{
  assert(rpScript == NULL);
  if (NULL != rpScript) return false;
  rpScript = new c4g::script::CScript();
  return true;
}

bool DestroyModule(c4g::core::IModule*& rpScript)
{
  assert(rpScript != NULL);
  if (NULL == rpScript) return false;
  delete rpScript;
  rpScript = NULL;
  return true;
}

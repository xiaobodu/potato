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

/*if (NULL == s)
{
  TCCState *s = tcc_new();
  tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
  tcc_set_error_func(s, 0, error_callback);

  if (tcc_compile_string(s, "int main(int argc, char* argv[]) { int a = 10; int b = 20; int c = a + b; log_info(\"hello world\"); return 0; }") == -1)
      return 1;
  tcc_add_symbol(s, "printf", (void const*)android_printf);
  tcc_add_symbol(s, "add", (void const*)add);
  //tcc_relocate(s, TCC_RELOCATE_AUTO);
  tcc_run(s, 0, NULL);
  tcc_delete(s);
}*/

CScript::CScript(const base::Config& roConfig)
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
  m_bCompiled = (-1 != tcc_compile_string(m_pTCC, rsCode.c_str()));
  if (m_bCompiled)
  {
    m_bCompiled = (tcc_relocate(m_pTCC, TCC_RELOCATE_AUTO) >= 0);
  }
}

void* const CSubstance::GetSymbol(const std::string& rsFuncName)
{
  if (!m_bCompiled) return NULL;

  return tcc_get_symbol(m_pTCC, rsFuncName.c_str());
}

}
}

bool CreateScript(c4g::core::IScript*& rpScript, const c4g::base::Config& roConfig)
{
  assert(rpScript == NULL);
  if (NULL != rpScript) return false;
  rpScript = new c4g::script::CScript(roConfig);
  return true;
}

bool DestroyScript(c4g::core::IScript*& rpScript, const c4g::base::Config& roConfig)
{
  assert(rpScript != NULL);
  if (NULL == rpScript) return false;
  delete rpScript;
  rpScript = NULL;
  return true;
}

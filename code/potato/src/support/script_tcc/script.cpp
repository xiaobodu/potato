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


void android_printf(char* txt)
{
  c4g::utility::Log::Instance().Info(txt);
}
int add(int a, int b)
{
    return a + b;
}
void error_callback(void *opaque, const char *msg)
{
  c4g::utility::Log::Instance().Info(msg);
}

/*if (NULL == s)
{
  TCCState *s = tcc_new();
  tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
  tcc_set_error_func(s, 0, error_callback);

  if (tcc_compile_string(s, "int main(int argc, char* argv[]) { int a = 10; int b = 20; int c = a + b; printf(\"hello world\"); return 0; }") == -1)
      return 1;
  tcc_add_symbol(s, "printf", (void const*)android_printf);
  tcc_add_symbol(s, "add", (void const*)add);
  //tcc_relocate(s, TCC_RELOCATE_AUTO);
  tcc_run(s, 0, NULL);
  tcc_delete(s);
}*/

CScript::CScript(const base::Config& roConfig)
{
  m_pTCC = tcc_new();
  if (NULL != m_pTCC)
  {
    tcc_set_output_type(m_pTCC, TCC_OUTPUT_MEMORY);
    tcc_set_error_func(m_pTCC, NULL, error_callback);

    // some common symbols
    tcc_add_symbol(m_pTCC, "log", (void const*)android_printf);
    tcc_add_symbol(m_pTCC, "add", (void const*)add);
  }
}

CScript::~CScript()
{
  // TODO: delete all script objects by the list of handlers
  if (NULL != m_pTCC)
  {
    tcc_delete(m_pTCC);
    m_pTCC = NULL;
  }
}

void CScript::New(script::AHandler* const& rpHandler)
{
  // TODO:
}

void CScript::Delete(script::AHandler* const& rpHandler)
{
  // TODO:
}

CObject::CObject()
{
  ;
}

CObject::~CObject()
{
  ;
}

void CObject::Call(const std::string& rsFuncName)
{
  ;
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

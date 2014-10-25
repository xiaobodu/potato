#include "potato.h"

#include "utility/sharedlibrary.h"
#include "utility/file.h"
#include "utility/log.h"

#if defined(CXX_MSVC)
#include <crtdbg.h>
#endif


#if !defined(BUILD_ANDROID)
#include "common.h"

namespace c4g {

/*!
 * \class Potato
 * \brief A main entry of the application
 */
class Potato
{
public:
  static Potato& Instance(const std::string& rsLibrPath = ".");

protected:
  Potato(const std::string& rsLibrPath = ".");
  virtual ~Potato();

public:
  Potato& Initialize();
  core::IEngine*& GetEngine();

private:
  core::IEngine* m_pEngine;
  core::MString2Module m_mModule;
};

}
#endif

#include <map>

namespace c4g {

static utility::CSharedLibraryManager gs_SharedLibraryManager;

Potato& Potato::Instance(const std::string& rsLibrPath /*= "."*/)
{
  static Potato s_potato(rsLibrPath);
  return s_potato;
}

Potato::Potato(const std::string& rsLibrPath /*= "."*/)
  : m_pEngine(NULL)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  C4G_LOG_INFO("the library path - %s", rsLibrPath.c_str());

  std::vector<std::string> file_list;
#if defined(CXX_MSVC)
  if (utility::GetListFiles(rsLibrPath, file_list, "*.dll") && !file_list.empty())
#else
  if (utility::GetListFiles(rsLibrPath, file_list) && !file_list.empty())
#endif
  {
    std::vector<std::string>::iterator it = file_list.begin();
    std::vector<std::string>::iterator it_end = file_list.end();
    for (; it != it_end; ++it)
    {
      //C4G_LOG_INFO("try to load the module file - %s", (*it).c_str());
      core::IModule::CreateModuleFuncPtr create_func_ptr = gs_SharedLibraryManager.GetFunc<core::IModule::CreateModuleFuncPtr>(*it, TOSTRING(CreateModule));
      core::IModule::DestroyModuleFuncPtr destroy_func_ptr = gs_SharedLibraryManager.GetFunc<core::IModule::DestroyModuleFuncPtr>(*it, TOSTRING(DestroyModule));
      if (NULL == create_func_ptr || NULL == destroy_func_ptr) continue;
      core::IModule* module_ptr = NULL;
      create_func_ptr(module_ptr);
      if (NULL == module_ptr) continue;
      module_ptr->m_pCreateFunc = create_func_ptr;
      module_ptr->m_pDestroyFunc = destroy_func_ptr;
      m_mModule.insert(std::make_pair(*module_ptr->type, module_ptr));
      //C4G_LOG_INFO("success to load the module file -%s", (*it).c_str());
    }
  }
}

Potato::~Potato()
{
  m_pEngine = NULL;

  if (!m_mModule.empty())
  {
    core::MString2Module::iterator it = m_mModule.begin();
    core::MString2Module::iterator it_end = m_mModule.end();
    for (; it != it_end; ++it)
    {
      core::IModule::Destroy(it->second);
    }
    m_mModule.clear();
  }
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

Potato& Potato::Initialize()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_pEngine = core::IModule::Find<core::IEngine>(m_mModule, MODULE_TYPE_ENGINE);
  if (NULL != m_pEngine) m_pEngine->Initialize(m_mModule);
  return *this;
}

core::IEngine*& Potato::GetEngine()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  assert(NULL != m_pEngine);
  return m_pEngine;
}

void ParseArgs(TMapStr2Str& rmArgs, const int& riSize, const char* const paArgv[], int iPos)
{
  if (iPos >= riSize) return;
  if ('-' != paArgv[iPos][0] || '-' != paArgv[iPos][1]) return;

  std::string key;
  key.append(paArgv[iPos] + 2);
  ++iPos;

  std::string value;
  while (iPos < riSize)
  {
    if ('-' == paArgv[iPos][0] && '-' == paArgv[iPos][1]) break;
    if (!value.empty()) value.append(" ");
    value.append(paArgv[iPos]);
    ++iPos;
  }
  rmArgs.insert(std::make_pair(key, value));

  ParseArgs(rmArgs, riSize, paArgv, iPos);
}

}

#if !defined(BUILD_ANDROID)
int main(int argc, char* argv[])
{
#if defined(CXX_MSVC)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  TMapStr2Str args;
  if (!GetConfig(args))
  {
    return 0;
  }

  c4g::ParseArgs(args, argc - 1, argv + 1, 0);

  TMapStr2Str::const_iterator cit_module = args.find("module");
  TMapStr2Str::const_iterator cit_data = args.find("data");
  if (cit_module == args.end() || cit_data == args.end())
  {
    printf("Usage: ** --module [PATH] --data [PATH]\n");
    return 0;
  }
  std::string module_path = cit_module->second;
  std::string data_path = cit_data->second;
  c4g::core::IEngine*& engine_ptr = c4g::Potato::Instance(module_path).Initialize().GetEngine();
  if (NULL != engine_ptr) engine_ptr->Run(data_path);
  return 0;
}
#endif

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
  if (utility::GetListFiles(rsLibrPath, file_list) && !file_list.empty())
  {
    std::vector<std::string>::iterator it = file_list.begin();
    std::vector<std::string>::iterator it_end = file_list.end();
    for (; it != it_end; ++it)
    {
      C4G_LOG_INFO("try to load the module file - %s", (*it).c_str());
      core::IModule::CreateModuleFuncPtr create_func_ptr = gs_SharedLibraryManager.GetFunc<core::IModule::CreateModuleFuncPtr>(*it, TOSTRING(CreateModule));
      core::IModule::DestroyModuleFuncPtr destroy_func_ptr = gs_SharedLibraryManager.GetFunc<core::IModule::DestroyModuleFuncPtr>(*it, TOSTRING(DestroyModule));
      if (NULL == create_func_ptr || NULL == destroy_func_ptr) continue;
      core::IModule* module_ptr = NULL;
      create_func_ptr(module_ptr);
      if (NULL == module_ptr) continue;
      module_ptr->m_pCreateFunc = create_func_ptr;
      module_ptr->m_pDestroyFunc = destroy_func_ptr;
      m_mModule.insert(std::make_pair(module_ptr->type, module_ptr));
      C4G_LOG_INFO("success to load the module file -%s", (*it).c_str());
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

}

#if !defined(BUILD_ANDROID)
int main(int argc, char* argv[])
{
#if defined(CXX_MSVC)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  std::string data_path;
  if (!GetConfig(data_path))
  {
    return 0;
  }
  c4g::core::IEngine*& engine_ptr = c4g::Potato::Instance().Initialize().GetEngine();
  if (NULL != engine_ptr) engine_ptr->Run(data_path);
  return 0;
}
#endif

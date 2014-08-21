#include "potato.h"

#include "dynamiclibrary.h"

FUNC_API_TYPEDEF(CreateEngine, ac::core::IEngine);
FUNC_API_TYPEDEF(DestroyEngine, ac::core::IEngine);

namespace ac {

Potato& Potato::Instance(const std::string& rsConfigPath)
{
  static Potato gs_potato(rsConfigPath);
  return gs_potato;
}

Potato::Potato(const std::string& rsConfigPath) :
    m_pEngine(NULL), m_sConfigPath(rsConfigPath)
{
  typedef FUNC_API_TYPE(CreateEngine) CreateEngineFuncPtr;
  CreateEngineFuncPtr func_create_func_ptr = tool::CDynamicLibraryManager::Instance().GetFunc<CreateEngineFuncPtr>(m_sConfigPath, TOSTRING(FUNC_API_TYPE(CreateEngine)));
  func_create_func_ptr(m_pEngine);
}

Potato::~Potato()
{
  typedef FUNC_API_TYPE(DestroyEngine) DestroyEngineFuncPtr;
  //DestroyEngineFuncPtr func_destroy_func_ptr = tool::CDynamicLibraryManager::Instance().GetFunc<DestroyEngineFuncPtr>(m_sConfigPath, TOSTRING(FUNC_API_NAME(DestroyEngine)));
  //func_destroy_func_ptr(m_pEngine);
}

core::IEngine*& Potato::GetEngine()
{
  return m_pEngine;
}
}

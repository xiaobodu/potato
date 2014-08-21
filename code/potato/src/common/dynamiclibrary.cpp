#include "dynamiclibrary.h"

#include <dlfcn.h>
#include <cassert>

namespace ac{
namespace tool{

CDynamicLibraryManager& CDynamicLibraryManager::Instance()
{
  static CDynamicLibraryManager gs_dynamic_libraries;
  return gs_dynamic_libraries;
}

CDynamicLibraryManager::CDynamicLibraryManager()
{
  m_mapFileName2Handler.clear();
}

void* CDynamicLibraryManager::GetFunc(const std::string& rsFileName, const std::string& rsFuncName)
{
  MapString2Handler::iterator cit = m_mapFileName2Handler.find(rsFileName);
  if (cit != m_mapFileName2Handler.end())
  {
    return cit->second.GetFunc(rsFuncName);
  }

  CDynamicLibraryHandler handler(rsFileName);
  m_mapFileName2Handler.insert(std::make_pair(rsFileName, handler));
  return handler.GetFunc(rsFuncName);
}

CDynamicLibraryManager::CDynamicLibraryHandler::CDynamicLibraryHandler(const std::string& rsFileName)
  : m_pLib(NULL)
{
  void* lib_ptr = dlopen(rsFileName.c_str(), RTLD_LAZY);
  assert(lib_ptr != NULL);
}

CDynamicLibraryManager::CDynamicLibraryHandler::~CDynamicLibraryHandler()
{
  dlclose(m_pLib);
}

void* CDynamicLibraryManager::CDynamicLibraryHandler::GetFunc(const std::string& rsFuncName)
{
  void* func_ptr = dlsym(m_pLib, rsFuncName.c_str());
  assert(func_ptr != NULL);
  m_mapFuncName2FunPtr.insert(std::make_pair(rsFuncName, func_ptr));
  return func_ptr;
}

}
}

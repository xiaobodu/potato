#include "util_dl.h"

#include <dlfcn.h>
#include <cassert>

namespace ac{
namespace utility{

DynamicLibraryManager& DynamicLibraryManager::Instance()
{
  static DynamicLibraryManager gs_instance;
  return gs_instance;
}

DynamicLibraryManager::DynamicLibraryManager()
{
  ;
}

DynamicLibraryManager::~DynamicLibraryManager()
{
  MapString2Handler::iterator it = m_mapFileName2Handler.begin();
  MapString2Handler::iterator it_end = m_mapFileName2Handler.end();
  for (; it != it_end; ++it)
  {
    delete it->second;
  }

  m_mapFileName2Handler.clear();
}

void* DynamicLibraryManager::GetFuncPtr(const std::string& rsFileName, const std::string& rsFuncName)
{
  MapString2Handler::iterator it = m_mapFileName2Handler.find(rsFileName);
  if (it != m_mapFileName2Handler.end())
  {
    return it->second->GetFunc(rsFuncName);
  }

  CDynamicLibraryHandler* handler_ptr = new CDynamicLibraryHandler(rsFileName);
  m_mapFileName2Handler.insert(std::make_pair(rsFileName, handler_ptr));
  return handler_ptr->GetFunc(rsFuncName);
}

DynamicLibraryManager::CDynamicLibraryHandler::CDynamicLibraryHandler(const std::string& rsFileName)
  : m_pLib(NULL)
{
  m_pLib = dlopen(rsFileName.c_str(), RTLD_LAZY);
  assert(m_pLib != NULL);
}

DynamicLibraryManager::CDynamicLibraryHandler::~CDynamicLibraryHandler()
{
#if !defined(BUILD_DEBUG)
  dlclose(m_pLib);
#endif
}

void* DynamicLibraryManager::CDynamicLibraryHandler::GetFunc(const std::string& rsFuncName)
{
  void* func_ptr = dlsym(m_pLib, rsFuncName.c_str());
  assert(func_ptr != NULL);
  m_mapFuncName2FunPtr.insert(std::make_pair(rsFuncName, func_ptr));
  return func_ptr;
}

}
}
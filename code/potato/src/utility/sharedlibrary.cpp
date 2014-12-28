#include "sharedlibrary.h"
#include "log.h"

#if defined(CXX_GNU) || defined(CXX_CLANG)
# include <dlfcn.h>
#elif defined(CXX_MSVC)
# include <Windows.h>
#endif
#include <iostream>

namespace c4g {
namespace utility {

CSharedLibraryHandler::CSharedLibraryHandler(const std::string& rsFileName)
    : m_pLib(NULL)
{
#if defined(CXX_GNU) || defined(CXX_CLANG)
  m_pLib = dlopen(rsFileName.c_str(), RTLD_LAZY);
#elif defined(CXX_MSVC)
  m_pLib = LoadLibrary(rsFileName.c_str());
#endif
}

CSharedLibraryHandler::~CSharedLibraryHandler()
{
  if (NULL == m_pLib) return;
#if defined(CXX_GNU) || defined(CXX_CLANG)
  dlclose(m_pLib);
#elif defined(CXX_MSVC)
  FreeLibrary((HMODULE)m_pLib);
#endif
}

void* CSharedLibraryHandler::GetFunc(const std::string& rsFuncName)
{
  void* func_ptr = NULL;
#if defined(CXX_GNU) || defined(CXX_CLANG)
  func_ptr = dlsym(m_pLib, rsFuncName.c_str());
#elif defined(CXX_MSVC)
  func_ptr = GetProcAddress((HMODULE)m_pLib, rsFuncName.c_str());
#endif
  m_mapFuncName2FunPtr.insert(std::make_pair(rsFuncName, func_ptr));
  return func_ptr;
}

CSharedLibraryManager::CSharedLibraryManager()
{
  ;
}

CSharedLibraryManager::~CSharedLibraryManager()
{
  MapString2Handler::iterator it = m_mapFileName2Handler.begin();
  MapString2Handler::iterator it_end = m_mapFileName2Handler.end();
  for (; it != it_end; ++it)
  {
    delete it->second;
  }

  m_mapFileName2Handler.clear();
}

void* CSharedLibraryManager::GetFuncPtr(const std::string& rsFileName, const std::string& rsFuncName)
{
  MapString2Handler::iterator it = m_mapFileName2Handler.find(rsFileName);
  if (it != m_mapFileName2Handler.end())
  {
    return it->second->GetFunc(rsFuncName);
  }

  CSharedLibraryHandler* handler_ptr = new CSharedLibraryHandler(rsFileName);
  m_mapFileName2Handler.insert(std::make_pair(rsFileName, handler_ptr));
  return handler_ptr->GetFunc(rsFuncName);
}

}
}

#include "sharedlibrary.h"
#include "log.h"

#include <dlfcn.h>
#include <cassert>
#include <iostream>

namespace c4g {
namespace utility {

CSharedLibraryHandler::CSharedLibraryHandler(const std::string& rsFileName)
    : m_pLib(NULL)
{
  m_pLib = dlopen(rsFileName.c_str(), RTLD_LAZY);
  utility::Log::Instance().Info("%s: %s res:%d", __PRETTY_FUNCTION__, rsFileName.c_str(), m_pLib);
  assert(m_pLib != NULL);
}

CSharedLibraryHandler::~CSharedLibraryHandler()
{
//#if !defined(BUILD_DEBUG)
  dlclose(m_pLib);
//#endif
}

void* CSharedLibraryHandler::GetFunc(const std::string& rsFuncName)
{
  void* func_ptr = dlsym(m_pLib, rsFuncName.c_str());
  utility::Log::Instance().Info("%s: %s res:%d", __PRETTY_FUNCTION__, rsFuncName.c_str(), m_pLib);
  assert(func_ptr != NULL);
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

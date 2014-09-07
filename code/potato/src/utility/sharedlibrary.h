#pragma once

#include <map>
#include <string>

namespace c4g {
namespace utility {

class CSharedLibraryHandler
{
public:
  CSharedLibraryHandler(const std::string& rsFileName);
  virtual ~CSharedLibraryHandler();

public:
  void* GetFunc(const std::string& rsFuncName);

private:
  void* m_pLib;
  std::map<std::string, void*> m_mapFuncName2FunPtr;
};

// a shared library manage interface
class CSharedLibraryManager
{
public:
  CSharedLibraryManager();
  virtual ~CSharedLibraryManager();

public:
  virtual void* GetFuncPtr(const std::string& rsFileName, const std::string& rsFuncName);

private:
  typedef std::map<std::string, CSharedLibraryHandler*> MapString2Handler;
  MapString2Handler m_mapFileName2Handler;

  // help to call by template
public:
  template<typename TFuncPtr>
  TFuncPtr GetFunc(const std::string& rsFileName, const std::string& rsFuncName)
  {
    return reinterpret_cast<TFuncPtr>(GetFuncPtr(rsFileName, rsFuncName));
  }
};

}
}

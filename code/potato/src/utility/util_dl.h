#pragma once

#include <map>
#include <string>

namespace c4g {
namespace utility {

class CDynamicLibraryHandler
{
public:
  CDynamicLibraryHandler(const std::string& rsFileName);
  virtual ~CDynamicLibraryHandler();

public:
  void* GetFunc(const std::string& rsFuncName);

private:
  void* m_pLib;
  std::map<std::string, void*> m_mapFuncName2FunPtr;
};

// a dynamic library manage interface
class DynamicLibraryManager
{
public:
  DynamicLibraryManager();
  virtual ~DynamicLibraryManager();

public:
  virtual void* GetFuncPtr(const std::string& rsFileName, const std::string& rsFuncName);

private:
  typedef std::map<std::string, CDynamicLibraryHandler*> MapString2Handler;
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

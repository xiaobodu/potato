#pragma once

#include "common.h"

#include <map>
#include <string>

namespace ac{
namespace tool{

// a dynamic library manage interface
class CDynamicLibraryManager
{
  class CDynamicLibraryHandler;

public:
  static CDynamicLibraryManager& Instance();

protected:
  CDynamicLibraryManager();
  virtual ~CDynamicLibraryManager();

public:
  virtual void* GetFunc(const std::string& rsFileName, const std::string& rsFuncName);

private:
  typedef std::map<std::string, CDynamicLibraryHandler> MapString2Handler;
  MapString2Handler m_mapFileName2Handler;

  // help to call by template
public:
  template<typename TFuncPtr>
  TFuncPtr GetFunc(const std::string& rsFileName, const std::string& rsFuncName)
  {
    return reinterpret_cast<TFuncPtr>(GetFunc(rsFileName, rsFuncName));
  }

private:
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
};

}
}

#pragma once

#include <map>
#include <string>

namespace ac{
namespace utility{

// a dynamic library manage interface
class DynamicLibraryManager
{
public:
  static DynamicLibraryManager& Instance();

protected:
  DynamicLibraryManager();
  virtual ~DynamicLibraryManager();

public:
  virtual void* GetFunc(const std::string& rsFileName, const std::string& rsFuncName);

private:
  class CDynamicLibraryHandler;
  typedef std::map<std::string, CDynamicLibraryHandler*> MapString2Handler;
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

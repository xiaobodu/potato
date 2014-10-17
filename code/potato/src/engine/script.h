#pragma once

#include "base.h"

#include <cassert>

#define MODULE_TYPE_SCRIPT    "script"

namespace c4g {

namespace script {
class ISubstance;
class AHandler;
}

namespace core {

class C4G_API IScript : public IModule
{
public:
  explicit IScript()
    : IModule(MODULE_TYPE_SCRIPT)
  {
    ;
  }
  virtual ~IScript()
  {
    ;
  }

public:
  virtual void New(script::AHandler* const& rpHandler) = 0;
  virtual void Delete(script::AHandler* const& rpHandler) = 0;
};

}

namespace script {

class ISubstance
{
public:
  virtual ~ISubstance()
  {
    ;
  }

public:
  virtual void Compile(const std::string& rsCode) = 0;
  virtual bool SetSymbol(const std::string& rsFuncName, void* pFunc) = 0;
  virtual void* const GetSymbol(const std::string& rsFuncName) = 0;
};

class AHandler
{
public:
  AHandler()
    : m_pScript(NULL)
    , m_pSubstance(NULL)
  {
    ;
  }
  virtual ~AHandler()
  {
    if (NULL != m_pSubstance)
    {
      assert(NULL != m_pScript);
      m_pScript->Delete(this);
    }
  }

public:
  bool HaveSubstance() const
  {
    return (NULL != m_pSubstance);
  }
  void OnNewSubstance(core::IScript* const& rpScript, ISubstance* const& rpSubstance)
  {
    m_pScript = rpScript;
    m_pSubstance = rpSubstance;
  }
  void OnDeleteSubstance()
  {
    m_pScript = NULL;
    m_pSubstance = NULL;
  }

private:
  core::IScript* m_pScript;

protected:
  ISubstance* m_pSubstance;
};

}

}

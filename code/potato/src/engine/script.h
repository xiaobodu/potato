#pragma once

#include "common.h"

namespace c4g {

namespace script {
class IObject;
class AHandler;
}

namespace core {

class IScript
{
public:
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

class IObject
{
public:
  virtual ~IObject()
  {
    ;
  }

public:
  virtual void Call(const std::string& rsFuncName) = 0;
};

class AHandler
{
public:
  AHandler()
    : m_pScript(NULL)
    , m_pScriptObj(NULL)
  {
    ;
  }
  virtual ~AHandler()
  {
    if (NULL != m_pScriptObj)
    {
      m_pScript->Delete(this);
    }
  }

private:
  void OnNewScriptObj(core::IScript* const& rpScript, IObject* const& rpObject)
  {
    m_pScript = rpScript;
    m_pScriptObj = rpObject;
  }
  void OnDeleteScriptObj()
  {
    m_pScriptObj = NULL;
  }

private:
  core::IScript* m_pScript;

protected:
  IObject* m_pScriptObj;
};

}

}

FUNC_API_DECLARE(CreateScript, c4g::core::IScript, const c4g::base::Config);
FUNC_API_DECLARE(DestroyScript, c4g::core::IScript, const c4g::base::Config);

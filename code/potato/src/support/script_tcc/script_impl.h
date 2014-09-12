#pragma once

#include "script.h"

struct TCCState;

namespace c4g {
namespace script {

class CScript : public core::IScript
{
public:
  explicit CScript(const base::Config& roConfig);
  virtual ~CScript();

public:
  virtual void New(script::AHandler* const& rpHandler);
  virtual void Delete(script::AHandler* const& rpHandler);

private:
  TCCState*  m_pTCC;
};

class CObject : public IObject
{
public:
  CObject();
  virtual ~CObject();

public:
  virtual void Call(const std::string& rsFuncName);
};

}
}

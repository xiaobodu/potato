#pragma once

#include "script.h"

#include <map>

struct TCCState;

namespace c4g {
namespace script {

class CScript : public core::IScript
{
public:
  explicit CScript();
  virtual ~CScript();

public:
  virtual bool Initialize(core::MString2Module& rmModule);

public:
  virtual void New(script::AHandler* const& rpHandler);
  virtual void Delete(script::AHandler* const& rpHandler);

private:
  typedef std::map<script::AHandler* const, ISubstance*>  MSubstance;
  MSubstance m_mSubstance;
};

class CSubstance : public ISubstance
{
public:
  CSubstance();
  virtual ~CSubstance();

public:
  virtual void Compile(const std::string& rsCode);
  virtual bool SetSymbol(const std::string& rsFuncName, void* pFunc);
  virtual void* const GetSymbol(const std::string& rsFuncName);

private:
  TCCState*  m_pTCC;
  bool m_bCompiled;
};

}
}

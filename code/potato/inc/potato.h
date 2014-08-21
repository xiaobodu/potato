#pragma once

#include <string>

namespace ac {

namespace core {

class IEngine
{
public:
  virtual ~IEngine()
  {
    ;
  }

public:
};

}

class Potato
{
public:
  static Potato& Instance(const std::string& rsConfigPath);

protected:
  Potato(const std::string& rsConfigPath);
  virtual ~Potato();

public:
  core::IEngine*& GetEngine();

private:
  std::string m_sConfigPath;
  core::IEngine* m_pEngine;
};

}

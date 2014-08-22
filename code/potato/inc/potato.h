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
  static Potato& Instance(const std::string& rsDataPath, const std::string& rsConfigFile);

protected:
  Potato(const std::string& rsDataPath, const std::string& rsConfigFile);
  virtual ~Potato();

public:
  core::IEngine*& GetEngine();

private:
  core::IEngine* m_pEngine;
};

}

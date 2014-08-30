// Copyright (c) 2014, Alex Chi (alexchicn@gmail.com)
#pragma once

#include <string>

#if defined(BUILD_ANDROID)
#include "common.h"

namespace ac {

/*!
 * \class Potato
 * \brief A main entry of the application
 */
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
  ac::base::Config m_oConfigEngine;
  core::IEngine* m_pEngine;
};

}
#endif

extern void GetConfig(std::string& rsPath, std::string& rsFile);

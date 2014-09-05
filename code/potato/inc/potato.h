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
  static Potato& Instance();

protected:
  Potato();
  virtual ~Potato();

public:
  Potato& Initialize(const std::string& rsLibPath, const std::string& rsDataPath, const std::string& rsConfigFile);
  core::IEngine*& GetEngine();

private:
  ac::base::Config m_oConfigEngine;
  core::IEngine* m_pEngine;
};

}

extern "C" void potato_main(struct android_app* pApp, const std::string& rsNativeClassName, const std::string& rsHelperClassName);

#endif

extern void GetConfig(std::string& rsPath, std::string& rsFile);

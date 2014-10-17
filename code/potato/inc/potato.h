// Copyright (c) 2014, Alex Chi (alexchicn@gmail.com)
#pragma once

#include <string>

extern bool GetConfig(std::string& rsDataPath);

#if defined(BUILD_ANDROID)
#include "common.h"

namespace c4g {

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
  Potato& Initialize(const std::string& rsDataPath);
  core::IEngine*& GetEngine();

private:
  core::IEngine* m_pEngine;
  core::MString2Module m_mModule;
};

}

extern "C" void potato_main(struct android_app* pApp, const std::string& rsNativeClassName, const std::string& rsHelperClassName);

#endif

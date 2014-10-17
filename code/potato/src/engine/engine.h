#pragma once

#include "base.h"
#include "potato.h"

#include <string>

namespace c4g {
namespace core {
class IDisplay;
class IScene;
}
namespace utility{
class CSharedLibraryManager;
}

namespace engine {

class CEngine : public core::IEngine
{
public:
  explicit CEngine();
  virtual ~CEngine();

public:
  virtual bool Initialize(core::MString2Module& rmModule);

public:
#if defined(BUILD_ANDROID)
  virtual void Run(const std::string& rsDataPath, android_app* pApp);
#else
  virtual void Run(const std::string& rsDataPath);
#endif

private:
  core::IDisplay*       m_pDisplay;
  core::IScene*         m_pScene;
};

}
}

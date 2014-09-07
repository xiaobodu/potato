#pragma once

#include "common.h"
#include "potato.h"

#include <string>

namespace c4g{
namespace core {
class IScene;
}
namespace utility{
class CSharedLibraryManager;
}

namespace core{

class IDisplay;

class CEngine : public IEngine
{
public:
  CEngine(const c4g::base::Config& roConfig);
  virtual ~CEngine();

public:
#if defined(BUILD_ANDROID)
  virtual void Run(android_app* pApp);
#else
  virtual void Run();
#endif

private:
  base::Config          m_oConfigDisplay;
  core::IDisplay*       m_pDisplay;
  base::Config          m_oConfigScene;
  core::IScene*         m_pScene;
  utility::CSharedLibraryManager* m_pLibraryManager;
};

}
}

FUNC_API_DECLARE(CreateEngine, c4g::core::IEngine, const c4g::base::Config);
FUNC_API_DECLARE(DestroyEngine, c4g::core::IEngine, const c4g::base::Config);

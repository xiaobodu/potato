#include "engine.h"
#include "display.h"
#include "scene.h"

#include "utility/thread.h"

#include "utility/log.h"
#include "utility/file.h"
#include "utility/sharedlibrary.h"

#include <cassert>
#if defined(OS_IS_LINUX)
#include <unistd.h>
#elif defined(OS_IS_WINDOWS)
#include <windows.h>
#endif
#include <string>

namespace c4g {
namespace engine {

CEngine::CEngine()
  : m_pDisplay(NULL)
  , m_pScene(NULL)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

CEngine::~CEngine()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
  
  m_pScene = NULL;
  m_pDisplay = NULL;
}

bool CEngine::Initialize(core::MString2Module& rmModule)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_pScene = IModule::Find<core::IScene>(rmModule, MODULE_TYPE_SCENE);
  m_pScene->Initialize(rmModule);
  m_pDisplay = IModule::Find<core::IDisplay>(rmModule, MODULE_TYPE_DISPLAY);
  m_pDisplay->Initialize(rmModule);
  return true;
}

/*class DisplayWorker : public thread::IWorker
{
public:
  DisplayWorker(IDisplay*& rpDisplay)
    : m_pDisplay(rpDisplay)
  {
    assert(NULL != rpDisplay);
  }
  virtual ~DisplayWorker() { ; }

  virtual void Do()
  {
    utility::Log::Instance().System("start the display work");

    m_pDisplay->Run(NULL);

    utility::Log::Instance().System("end the display work");
  }

private:
  IDisplay* m_pDisplay;
};*/

#if defined(BUILD_ANDROID)
void CEngine::Run(const std::string& rsDataPath, android_app* pApp)
#else
void CEngine::Run(const std::string& rsDataPath)
#endif
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_pScene->SetDataPath(rsDataPath);

#if defined(BUILD_ANDROID)
  m_pDisplay->BindAndroidApp(pApp);
#endif
  m_pDisplay->Run(m_pScene);

  // use multi-thread in the future
  /*DisplayWorker display_worker(m_pDisplay);
  thread::IWorker* workers[] = {&display_worker};
  thread::DoJob(workers, 1);*/
}

}
}

bool CreateModule(c4g::core::IModule*& rpEngine)
{
  assert(rpEngine == NULL);
  rpEngine = new c4g::engine::CEngine();
  return true;
}

bool DestroyModule(c4g::core::IModule*& rpEngine)
{
  assert(rpEngine != NULL);
  delete rpEngine;
  rpEngine = NULL;
  return true;
}

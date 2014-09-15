#include <cassert>
#include <unistd.h>
#include <string>

#include <rapidjson/document.h>

#include "engine.h"
#include "display.h"
#include "scene.h"

#include "utility/thread.h"

#include "utility/log.h"
#include "utility/file.h"
#include "utility/sharedlibrary.h"

FUNC_API_TYPEDEF(CreateDisplay, c4g::core::IDisplay, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyDisplay, c4g::core::IDisplay, const c4g::base::Config);

FUNC_API_TYPEDEF(CreateScene, c4g::core::IScene, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyScene, c4g::core::IScene, const c4g::base::Config);

namespace c4g{
namespace core{

CEngine::CEngine(const c4g::base::Config& roConfig)
  : m_pDisplay(NULL)
  , m_pScene(NULL)
  , m_pLibraryManager(NULL)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  m_pLibraryManager = new utility::CSharedLibraryManager();

#if defined(BUILD_ANDROID)
  std::string file_context = roConfig._sConfigureContext.c_str();
#else
  std::string file_context = utility::ReadFile(roConfig.GetConfigureFile());
#endif

  rapidjson::Document doc;
  doc.Parse(file_context.c_str());
  assert(doc.IsObject());

  /// build the display from the configure file
  {
    m_oConfigDisplay._sLibrPath = roConfig._sLibrPath;
    m_oConfigDisplay._sDataPath = roConfig._sDataPath;

    const rapidjson::Value& display = doc["display"];
    assert(display.IsObject());

    const rapidjson::Value& library = display["library"];
    assert(library.IsString());
    m_oConfigDisplay._sLibraryFile = library.GetString();

#if defined(BUILD_ANDROID)
    m_oConfigDisplay._sConfigureContext = "\
{\
  \"render\":{\
    \"library\":\"lib/librender_gles.so\"\
  }\
}";
#else
    const rapidjson::Value& configure = display["configure"];
    assert(configure.IsString());
    m_oConfigDisplay._sConfigureFile = configure.GetString();
#endif

    typedef FUNC_API_TYPE(CreateDisplay) CreateDisplayFuncPtr;
    /// load the shared library
    CreateDisplayFuncPtr func_create_func_ptr = m_pLibraryManager->GetFunc<CreateDisplayFuncPtr>(m_oConfigDisplay.GetLibraryFile(), TOSTRING(CreateDisplay));
    /// create the display with configure
    func_create_func_ptr(m_pDisplay, m_oConfigDisplay);
  }

  /// build the scene from the configure file
  {
    m_oConfigScene._sLibrPath = roConfig._sLibrPath;
    m_oConfigScene._sDataPath = roConfig._sDataPath;

    const rapidjson::Value& display = doc["scene"];
    assert(display.IsObject());
    const rapidjson::Value& library = display["library"];
    assert(library.IsString());
    m_oConfigScene._sLibraryFile = library.GetString();

#if defined(BUILD_ANDROID)
    m_oConfigScene._sConfigureContext = "\
{\
  \"asset\":{\
    \"library\":\"lib/libasset.so\"\
  },\
  \"flash\":{\
    \"library\":\"lib/libflash.so\"\
  },\
  \"script\":{\
    \"library\":\"lib/libscript_tcc.so\"\
  }\
}";
#else
    const rapidjson::Value& configure = display["configure"];
    assert(configure.IsString());
    m_oConfigScene._sConfigureFile = configure.GetString();
#endif

    typedef FUNC_API_TYPE(CreateScene) CreateSceneFuncPtr;
    /// load the shared library
    CreateSceneFuncPtr func_create_func_ptr = m_pLibraryManager->GetFunc<CreateSceneFuncPtr>(m_oConfigScene.GetLibraryFile(), TOSTRING(CreateScene));
    /// create the display with configure
    func_create_func_ptr(m_pScene, m_oConfigScene);
  }
}

CEngine::~CEngine()
{
  /// destroy the scene from the configure file
  {
    /// load the shared library
    typedef FUNC_API_TYPE(DestroyScene) DestroySceneFuncPtr;
    DestroySceneFuncPtr func_destroy_func_ptr = m_pLibraryManager->GetFunc<DestroySceneFuncPtr>(m_oConfigScene.GetLibraryFile(), TOSTRING(DestroyScene));
    /// create the display with configure
    func_destroy_func_ptr(m_pScene, m_oConfigScene);
  }

  /// destroy the display from the configure file
  {
    /// load the shared library
    typedef FUNC_API_TYPE(DestroyDisplay) DestroyDisplayFuncPtr;
    DestroyDisplayFuncPtr func_destroy_func_ptr = m_pLibraryManager->GetFunc<DestroyDisplayFuncPtr>(m_oConfigDisplay.GetLibraryFile(), TOSTRING(DestroyDisplay));
    /// create the display with configure
    func_destroy_func_ptr(m_pDisplay, m_oConfigDisplay);
  }

  delete m_pLibraryManager;
  m_pLibraryManager = NULL;

  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
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
void CEngine::Run(android_app* pApp)
#else
void CEngine::Run()
#endif
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

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

bool CreateEngine(c4g::core::IEngine*& rpEngine, const c4g::base::Config& roConfig)
{
  assert(rpEngine == NULL);
  rpEngine = new c4g::core::CEngine(roConfig);
  return true;
}

bool DestroyEngine(c4g::core::IEngine*& rpEngine, const c4g::base::Config& roConfig)
{
  assert(rpEngine != NULL);
  delete rpEngine;
  rpEngine = NULL;
  return true;
}

#include <cassert>
#include <unistd.h>
#include <string>

#include <rapidjson/document.h>

#include "engine.h"
#include "display.h"
#include "render.h"

#include "utility/thread.h"

#include "utility/log.h"
#include "utility/file.h"
#include "utility/sharedlibrary.h"

FUNC_API_TYPEDEF(CreateDisplay, c4g::core::IDisplay, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyDisplay, c4g::core::IDisplay, const c4g::base::Config);

namespace c4g{
namespace core{

CEngine::CEngine(const c4g::base::Config& roConfig)
  : m_pDisplay(NULL)
  , m_pLibraryManager(NULL)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  m_pLibraryManager = new utility::DynamicLibraryManager();

  std::string file_context = utility::ReadFile(roConfig.GetConfigureFile());

  rapidjson::Document doc;
  doc.Parse(file_context.c_str());
  assert(doc.IsObject());
  const rapidjson::Value& display = doc["display"];
  assert(display.IsObject());
  const rapidjson::Value& library = display["library"];
  assert(library.IsObject());
  const rapidjson::Value& library_file = library["file"];
  assert(library_file.IsString());
  const rapidjson::Value& configure = display["configure"];
  assert(configure.IsObject());
  const rapidjson::Value& configure_file = configure["file"];
  assert(configure_file.IsString());

  m_oConfigDisplay._sLibrPath = roConfig._sLibrPath;
  m_oConfigDisplay._sDataPath = roConfig._sDataPath;
  m_oConfigDisplay._sLibraryFile = library_file.GetString();
  m_oConfigDisplay._sConfigureFile = configure_file.GetString();

  /// load the dynamic library
  typedef FUNC_API_TYPE(CreateDisplay) CreateDisplayFuncPtr;
  CreateDisplayFuncPtr func_create_func_ptr = m_pLibraryManager->GetFunc<CreateDisplayFuncPtr>(m_oConfigDisplay.GetLibraryFile(), TOSTRING(CreateDisplay));
  /// create the display with configure
  func_create_func_ptr(m_pDisplay, m_oConfigDisplay);
}

CEngine::~CEngine()
{
  /// load the dynamic library
  typedef FUNC_API_TYPE(DestroyDisplay) DestroyDisplayFuncPtr;
  DestroyDisplayFuncPtr func_destroy_func_ptr = m_pLibraryManager->GetFunc<DestroyDisplayFuncPtr>(m_oConfigDisplay.GetLibraryFile(), TOSTRING(DestroyDisplay));
  /// create the display with configure
  func_destroy_func_ptr(m_pDisplay, m_oConfigDisplay);

  delete m_pLibraryManager;
  m_pLibraryManager = NULL;

  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

class DisplayWorker : public thread::IWorker
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

    m_pDisplay->Run();

    utility::Log::Instance().System("end the display work");
  }

private:
  IDisplay* m_pDisplay;
};

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
  m_pDisplay->Run();

  //DisplayWorker display_worker(m_pDisplay);
  //thread::IWorker* workers[] = {&display_worker};
  //thread::DoJob(workers, 1);
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

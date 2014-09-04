#include <cassert>
#include <unistd.h>
#include <string>

#include <rapidjson/document.h>

#include "engine.h"
#include "display.h"
#include "render.h"

#include "utility/thread.h"

#include "utility/util_log.h"
#include "utility/util_file.h"
#include "utility/util_dl.h"

FUNC_API_TYPEDEF(CreateDisplay, ac::core::IDisplay, const ac::base::Config);
FUNC_API_TYPEDEF(DestroyDisplay, ac::core::IDisplay, const ac::base::Config);

FUNC_API_TYPEDEF(CreateRender, ac::core::IRender, const ac::base::Config);
FUNC_API_TYPEDEF(DestroyRender, ac::core::IRender, const ac::base::Config);

namespace ac{
namespace core{

CEngine::CEngine(const ac::base::Config& roConfig)
  : m_pDisplay(NULL)
  , m_pRender(NULL)
{
  utility::Log::Instance().System("call the 'CEngine' constructor");

  std::string file_context = utility::ReadFile(roConfig.GetConfigureFile());

  rapidjson::Document doc;
  doc.Parse(file_context.c_str());
  assert(doc.IsObject());
  if (NULL == m_pDisplay)
  {
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
    CreateDisplayFuncPtr func_create_func_ptr = utility::DynamicLibraryManager::Instance().GetFunc<CreateDisplayFuncPtr>(m_oConfigDisplay.GetLibraryFile(), TOSTRING(CreateDisplay));
    /// create the display with configure
    func_create_func_ptr(m_pDisplay, m_oConfigDisplay);
  }
  if (NULL == m_pRender)
  {
    const rapidjson::Value& render = doc["render"];
    assert(render.IsObject());
    const rapidjson::Value& library = render["library"];
    assert(library.IsObject());
    const rapidjson::Value& library_file = library["file"];
    assert(library_file.IsString());
    const rapidjson::Value& configure = render["configure"];
    assert(configure.IsObject());
    const rapidjson::Value& configure_file = configure["file"];
    assert(configure_file.IsString());

    m_oConfigRender._sLibrPath = roConfig._sLibrPath;
    m_oConfigRender._sDataPath = roConfig._sDataPath;
    m_oConfigRender._sLibraryFile = library_file.GetString();
    m_oConfigRender._sConfigureFile = configure_file.GetString();

    /// load the dynamic library
    typedef FUNC_API_TYPE(CreateRender) CreateRenderFuncPtr;
    CreateRenderFuncPtr func_create_func_ptr = utility::DynamicLibraryManager::Instance().GetFunc<CreateRenderFuncPtr>(m_oConfigRender.GetLibraryFile(), TOSTRING(CreateRender));
    /// create the display with configure
    func_create_func_ptr(m_pRender, m_oConfigDisplay);
  }

  /// bind the render to the display
  m_pDisplay->BindRender(m_pRender);
}

CEngine::~CEngine()
{
  utility::Log::Instance().System("call the 'CEngine' destructor");

  {
    /// load the dynamic library
    typedef FUNC_API_TYPE(DestroyRender) DestroyRenderFuncPtr;
    DestroyRenderFuncPtr func_destroy_func_ptr = utility::DynamicLibraryManager::Instance().GetFunc<DestroyRenderFuncPtr>(m_oConfigRender.GetLibraryFile(), TOSTRING(DestroyRender));
    /// create the display with configure
    func_destroy_func_ptr(m_pRender, m_oConfigDisplay);
  }

  {
    /// load the dynamic library
    typedef FUNC_API_TYPE(DestroyDisplay) DestroyDisplayFuncPtr;
    DestroyDisplayFuncPtr func_destroy_func_ptr = utility::DynamicLibraryManager::Instance().GetFunc<DestroyDisplayFuncPtr>(m_oConfigDisplay.GetLibraryFile(), TOSTRING(DestroyDisplay));
    /// create the display with configure
    func_destroy_func_ptr(m_pDisplay, m_oConfigDisplay);
  }
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

    //m_pDisplay->Run();

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
  utility::Log::Instance().System("engine is running");

  //DisplayWorker display_worker(m_pDisplay);
  //thread::IWorker* workers[] = {&display_worker};
  //thread::DoJob(workers, 1);
#if defined(BUILD_ANDROID)
  m_pDisplay->Run(pApp);
#else
  m_pDisplay->Run();
#endif
}

}
}

bool CreateEngine(ac::core::IEngine*& rpEngine, const ac::base::Config& roConfig)
{
  assert(rpEngine == NULL);
  rpEngine = new ac::core::CEngine(roConfig);
  return true;
}

bool DestroyEngine(ac::core::IEngine*& rpEngine, const ac::base::Config& roConfig)
{
  assert(rpEngine != NULL);
  delete rpEngine;
  rpEngine = NULL;
  return true;
}

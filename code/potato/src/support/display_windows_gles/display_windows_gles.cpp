#include <rapidjson/document.h>

#include "display_windows_gles.h"

#include "render.h"
#include "scene.h"

#include "utility/file.h"
#include "utility/log.h"
#include "utility/sharedlibrary.h"

#include <cassert>
//#include <unistd.h>
//#include <sys/time.h>

FUNC_API_TYPEDEF(CreateRender, c4g::core::IRender, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyRender, c4g::core::IRender, const c4g::base::Config);

namespace c4g {
namespace display {
namespace linux_gles {

CDisplay::CDisplay(const base::Config& roConfig)
  : m_bIsRunning(true)
  , m_iWidth(0)
  , m_iHeight(0)
  , m_pRender(NULL)
  , m_pLibraryManager(NULL)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  m_pLibraryManager = new utility::CSharedLibraryManager();

  std::string file_context = utility::ReadFile(roConfig.GetConfigureFile());

  rapidjson::Document jdoc;
  jdoc.Parse(file_context.c_str());
  assert(jdoc.IsObject());
  const rapidjson::Value& jtitle = jdoc["title"];
  assert(jtitle.IsString());
  const rapidjson::Value& jsize = jdoc["size"];
  assert(jsize.IsObject());
  const rapidjson::Value& jwidth = jsize["width"];
  assert(jwidth.IsInt());
  const rapidjson::Value& jheight = jsize["height"];
  assert(jheight.IsInt());

  const rapidjson::Value& render = jdoc["render"];
  assert(render.IsObject());
  const rapidjson::Value& library = render["library"];
  assert(library.IsString());
  const rapidjson::Value& configure = render["configure"];
  assert(configure.IsString());

  m_sTitle = jtitle.GetString();
  m_iWidth = jwidth.GetInt();
  m_iHeight = jheight.GetInt();

  m_oConfigRender._sLibrPath = roConfig._sLibrPath;
  m_oConfigRender._sDataPath = roConfig._sDataPath;
  m_oConfigRender._sLibraryFile = library.GetString();
  m_oConfigRender._sConfigureFile = configure.GetString();

  /// load the shared library
  typedef FUNC_API_TYPE(CreateRender) CreateRenderFuncPtr;
  CreateRenderFuncPtr func_create_func_ptr = m_pLibraryManager->GetFunc<CreateRenderFuncPtr>(m_oConfigRender.GetLibraryFile(), TOSTRING(CreateRender));
  /// create the display with configure
  func_create_func_ptr(m_pRender, m_oConfigRender);
}

CDisplay::~CDisplay()
{
  /// load the CShared library
  typedef FUNC_API_TYPE(DestroyRender) DestroyRenderFuncPtr;
  DestroyRenderFuncPtr func_destroy_func_ptr = m_pLibraryManager->GetFunc<DestroyRenderFuncPtr>(m_oConfigRender.GetLibraryFile(), TOSTRING(DestroyRender));
  /// create the display with configure
  func_destroy_func_ptr(m_pRender, m_oConfigRender);

  delete m_pLibraryManager;
  m_pLibraryManager = NULL;

  utility::Log::Instance().Info(__PRETTY_FUNCTION__);
}

void CDisplay::Run(core::IScene* const& rpScene)
{
  utility::Log::Instance().Info(__PRETTY_FUNCTION__);

  CreateWindow();

  m_pRender->Start();
  //m_pRender->Resize(m_iWidth, m_iHeight);

  //TODO:
  rpScene->Load(m_pRender, "scene/root.json");
  rpScene->Resize(m_iWidth, m_iHeight);

  //TODO:

  rpScene->Unload(m_pRender);
  m_pRender->End();

  DestroyWindow();
}

void CDisplay::CreateWindow()
{
  //TODO:
}

void CDisplay::DestroyWindow()
{
  //TODO:
}

}
}
}

bool CreateDisplay(c4g::core::IDisplay*& rpDisplay, const c4g::base::Config& roConfig)
{
  assert(rpDisplay == NULL);
  rpDisplay = new c4g::display::linux_gles::CDisplay(roConfig);
  return true;
}

bool DestroyDisplay(c4g::core::IDisplay*& rpDisplay, const c4g::base::Config& roConfig)
{
  assert(rpDisplay != NULL);
  delete rpDisplay;
  rpDisplay = NULL;
  return true;
}

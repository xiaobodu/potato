#include <rapidjson/document.h>

#include "scene_impl.h"
#include "render.h"
#include "asset.h"

#include "panel.h"

#include "utility/file.h"
#include "utility/log.h"
#include "utility/sharedlibrary.h"

#include <cassert>

FUNC_API_TYPEDEF(CreateAsset, c4g::core::IAsset, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyAsset, c4g::core::IAsset, const c4g::base::Config);

namespace c4g {
namespace scene {

static render::Glyph g_Glyph;

class CProcess : public render::IProcess
{
public:
  CProcess() : angle(0.0f) { ; }
  virtual ~CProcess() { ; }

public:
  virtual void Begin(const render::Glyph& rGlyph) { ; }
  virtual bool Do(render::ITransform* const& rpTransform)
  {
    // think in the 3d transform
    rpTransform->Translate(100.0f, 100.0f);
    rpTransform->Rotate(angle, 0.0f, 0.0f, 1.0f, 150.0f, 150.0f, 0.0f);
    return true;
  }
  virtual void End() { ; }

public:
  bool Tick(const float& rfDelta)
  {
    angle += rfDelta * 20.0f;
    if (angle > 360.0f) angle-= 360.0f;
    return true;
  }

private:
  float angle;
};
static CProcess g_process;

CScene::CScene(const base::Config& roConfig)
  : m_pAsset(NULL)
  , m_pLibraryManager(NULL)
  , m_pPanel(NULL)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_oConfig = roConfig;
  m_pLibraryManager = new utility::CSharedLibraryManager();

#if defined(BUILD_ANDROID)
  std::string file_context = roConfig._sConfigureContext.c_str();
#else
  std::string file_context = utility::ReadFile(roConfig.GetConfigureFile());
#endif

  rapidjson::Document jdoc;
  jdoc.Parse(file_context.c_str());
  assert(jdoc.IsObject());

  m_oConfigAsset._sLibrPath = roConfig._sLibrPath;
  m_oConfigAsset._sDataPath = roConfig._sDataPath;

  const rapidjson::Value& render = jdoc["asset"];
  assert(render.IsObject());

  const rapidjson::Value& library = render["library"];
  assert(library.IsString());
  m_oConfigAsset._sLibraryFile = library.GetString();

#if defined(BUILD_ANDROID)
  m_oConfigAsset._sConfigureContext = "\
{\
  \"asset\":{\
    \"library\":\"lib/libasset.so\"\
  }\
}";
#else
  const rapidjson::Value& configure = render["configure"];
  assert(configure.IsString());
  m_oConfigAsset._sConfigureFile = library.GetString();
#endif

  /// load the shared library
  typedef FUNC_API_TYPE(CreateAsset) CreateAssetFuncPtr;
  CreateAssetFuncPtr func_create_func_ptr = m_pLibraryManager->GetFunc<CreateAssetFuncPtr>(m_oConfigAsset.GetLibraryFile(), TOSTRING(CreateAsset));
  /// create the display with configure
  func_create_func_ptr(m_pAsset, m_oConfigAsset);

  m_pPanel = new CPanel(this, NULL);
}

CScene::~CScene()
{
  delete m_pPanel;
  m_pPanel = NULL;

  /// load the shared library
  typedef FUNC_API_TYPE(DestroyAsset) DestroyAssetFuncPtr;
  DestroyAssetFuncPtr func_destroy_func_ptr = m_pLibraryManager->GetFunc<DestroyAssetFuncPtr>(m_oConfigAsset.GetLibraryFile(), TOSTRING(DestroyAsset));
  /// create the display with configure
  func_destroy_func_ptr(m_pAsset, m_oConfigAsset);

  delete m_pLibraryManager;
  m_pLibraryManager = NULL;

  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

bool CScene::Load(core::IRender* const& rpRender, const std::string& rsFileName)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  std::string file_context = utility::ReadFile(m_oConfig._sDataPath + "/" + rsFileName);
  rapidjson::Document jdoc;
  jdoc.Parse(file_context.c_str());
  CPanel::builder.Parser(m_pAsset, jdoc, m_pPanel);

  int width = 0;
  int height = 0;
  unsigned char* buffer_ptr = NULL;
  m_pAsset->LoadImage("res/icon.png", width, height, buffer_ptr);

  g_Glyph.l = 0.0f;
  g_Glyph.r = 1.0f;
  g_Glyph.t = 0.0f;
  g_Glyph.b = 1.0f;
  g_Glyph.id = rpRender->GenerateTexId(width, height, buffer_ptr);
  return true;
}

bool CScene::Unload(core::IRender* const& rpRender)
{
  rpRender->DeleteTexId(1, &g_Glyph.id);
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
  return true;
}

bool CScene::Resize(const int& riWidth, const int& riHeight)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_pPanel->Resize(riWidth, riHeight);
  return true;
}

bool CScene::Tick(const float& rfDelta)
{
  g_process.Tick(rfDelta);

  return m_pPanel->Tick(rfDelta);
}

bool CScene::Draw(render::ICanvas* const& rpCanvas)
{
  rpCanvas->DrawGlyph(g_Glyph, 300, 300, &g_process);

  m_pPanel->Draw(rpCanvas);
  return true;
}

bool CScene::Handle(const display::IInput* const& rpInput)
{
  return m_pPanel->Handle(rpInput);
}

}
}

bool CreateScene(c4g::core::IScene*& rpScene, const c4g::base::Config& roConfig)
{
  assert(rpScene == NULL);
  if (NULL != rpScene) return false;
  rpScene = new c4g::scene::CScene(roConfig);
  return true;
}

bool DestroyScene(c4g::core::IScene*& rpScene, const c4g::base::Config& roConfig)
{
  assert(rpScene != NULL);
  if (NULL == rpScene) return false;
  delete rpScene;
  rpScene = NULL;
  return true;
}

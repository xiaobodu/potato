#include <rapidjson/document.h>

#include "scene_impl.h"
#include "render.h"
#include "asset.h"

#include "scene_base.h"
#include "panel.h"

#include "utility/file.h"
#include "utility/log.h"
#include "utility/sharedlibrary.h"

#include <cassert>

FUNC_API_TYPEDEF(CreateAsset, c4g::core::IAsset, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyAsset, c4g::core::IAsset, const c4g::base::Config);

namespace c4g {
namespace scene {

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
  m_pPanel->layout.type = ELayoutType_Scale;
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

  //TODO:
  CAssetsBuilder::instance.BindRender(rpRender);

  std::string file_context = utility::ReadFile(m_oConfig._sDataPath + "/" + rsFileName);
  rapidjson::Document jdoc;
  jdoc.Parse(file_context.c_str());
  CPanel::builder.Do(m_pAsset, jdoc, m_pPanel);
  return true;
}

class CImageInfoVisitorUnload : public core::IAsset::IImageInfoVisitor
{
public:
  static CImageInfoVisitorUnload instance;

protected:
  CImageInfoVisitorUnload()
    : m_pRender(NULL)
  {
    ;
  }
  virtual ~CImageInfoVisitorUnload()
  {
    ;
  }

public:
  CImageInfoVisitorUnload& BindRender(core::IRender* const& rpRender)
  {
    m_pRender = rpRender;
    return (*this);
  }

public:
  virtual void On(const std::string& rsId, const int& riWidth, const int& riHeight, const unsigned int& riId) const
  {
    if (NULL == m_pRender) return;
    unsigned int id = riId;
    m_pRender->DeleteTexId(1, &id);
  }

private:
  core::IRender* m_pRender;
};
CImageInfoVisitorUnload CImageInfoVisitorUnload::instance;

bool CScene::Unload(core::IRender* const& rpRender)
{
  m_pAsset->VisitImageInfo(&CImageInfoVisitorUnload::instance.BindRender(rpRender));
  m_pAsset->ClearImageInfo();

  m_pPanel->Clear();

  C4G_LOG_INFO(__PRETTY_FUNCTION__);
  return true;
}

bool CScene::Resize(const int& riWidth, const int& riHeight)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  m_pPanel->dst(riWidth, riHeight);
  m_pPanel->Resize(riWidth, riHeight);
  return true;
}

bool CScene::Tick(const float& rfDelta)
{
  return m_pPanel->Tick(rfDelta);
}

bool CScene::Draw(render::ICanvas* const& rpCanvas)
{
  for (int i = C4G_LAYER_MIN; i < C4G_LAYER_MAX; ++i)
  {
    m_pPanel->Draw(i, rpCanvas);
  }
  return true;
}

bool CScene::Handle(const display::IInput* const& rpInput)
{
  bool res = false;
  for (int i = C4G_LAYER_MIN; i < C4G_LAYER_MAX; ++i)
  {
    res |= m_pPanel->Handle(i, rpInput);
  }
  return res;
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

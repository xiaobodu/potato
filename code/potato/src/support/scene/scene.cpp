#include <rapidjson/document.h>

#include "scene_base.h"
#include "scene_impl.h"
#include "panel.h"

#include "render.h"
#include "asset.h"
#include "script.h"
#include "input.h"

#include "utility/file.h"
#include "utility/log.h"
#include "utility/sharedlibrary.h"

#include <cassert>

FUNC_API_TYPEDEF(CreateAsset, c4g::core::IAsset, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyAsset, c4g::core::IAsset, const c4g::base::Config);

FUNC_API_TYPEDEF(CreateFlash, c4g::core::IFlash, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyFlash, c4g::core::IFlash, const c4g::base::Config);

FUNC_API_TYPEDEF(CreateScript, c4g::core::IScript, const c4g::base::Config);
FUNC_API_TYPEDEF(DestroyScript, c4g::core::IScript, const c4g::base::Config);

namespace c4g {
namespace scene {

CScene::CScene(const base::Config& roConfig)
  : m_pAsset(NULL)
  , m_pFlash(NULL)
  , m_pScript(NULL)
  , m_pLibraryManager(NULL)
  , m_pPanel(NULL)
  , m_bNeedFlush(true)
  , m_bPlayEffect(false)
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

  {
    m_oConfigAsset._sLibrPath = roConfig._sLibrPath;
    m_oConfigAsset._sDataPath = roConfig._sDataPath;

    const rapidjson::Value& jasset = jdoc["asset"];
    assert(jasset.IsObject());

    const rapidjson::Value& library = jasset["library"];
    assert(library.IsString());
    m_oConfigAsset._sLibraryFile = library.GetString();

#if defined(BUILD_ANDROID)
    m_oConfigAsset._sConfigureContext = "{}";
#else
    const rapidjson::Value& configure = jasset["configure"];
    assert(configure.IsString());
    m_oConfigAsset._sConfigureFile = configure.GetString();
#endif

    /// load the shared library
    typedef FUNC_API_TYPE(CreateAsset) CreateAssetFuncPtr;
    CreateAssetFuncPtr func_create_func_ptr = m_pLibraryManager->GetFunc<CreateAssetFuncPtr>(m_oConfigAsset.GetLibraryFile(), TOSTRING(CreateAsset));
    /// create the display with configure
    func_create_func_ptr(m_pAsset, m_oConfigAsset);
  }

  {
    m_oConfigFlash._sLibrPath = roConfig._sLibrPath;
    m_oConfigFlash._sDataPath = roConfig._sDataPath;

    const rapidjson::Value& jflash = jdoc["flash"];
    assert(jflash.IsObject());

    const rapidjson::Value& library = jflash["library"];
    assert(library.IsString());
    m_oConfigFlash._sLibraryFile = library.GetString();

#if defined(BUILD_ANDROID)
    m_oConfigFlash._sConfigureContext = "\
{\
  \"data\": \"flash/root.json\"\
}";
#else
    const rapidjson::Value& configure = jflash["configure"];
    assert(configure.IsString());
    m_oConfigFlash._sConfigureFile = configure.GetString();
#endif

    /// load the shared library
    typedef FUNC_API_TYPE(CreateFlash) CreateFlashFuncPtr;
    CreateFlashFuncPtr func_create_func_ptr = m_pLibraryManager->GetFunc<CreateFlashFuncPtr>(m_oConfigFlash.GetLibraryFile(), TOSTRING(CreateFlash));
    /// create the display with configure
    func_create_func_ptr(m_pFlash, m_oConfigFlash);
  }

  {
    m_oConfigScript._sLibrPath = roConfig._sLibrPath;
    m_oConfigScript._sDataPath = roConfig._sDataPath;

    const rapidjson::Value& jscript = jdoc["script"];
    assert(jscript.IsObject());

    const rapidjson::Value& library = jscript["library"];
    assert(library.IsString());
    m_oConfigScript._sLibraryFile = library.GetString();

#if defined(BUILD_ANDROID)
    m_oConfigScript._sConfigureContext = "{}";
#else
    const rapidjson::Value& configure = jscript["configure"];
    assert(configure.IsString());
    m_oConfigScript._sConfigureFile = library.GetString();
#endif

    /// load the shared library
    typedef FUNC_API_TYPE(CreateScript) CreateScriptFuncPtr;
    CreateScriptFuncPtr func_create_func_ptr = m_pLibraryManager->GetFunc<CreateScriptFuncPtr>(m_oConfigScript.GetLibraryFile(), TOSTRING(CreateScript));
    /// create the display with configure
    func_create_func_ptr(m_pScript, m_oConfigScript);
  }

  m_pPanel = new CPanel(this, NULL);
  m_pPanel->layout.type = ELayoutType_Scale;
}

CScene::~CScene()
{
  delete m_pPanel;
  m_pPanel = NULL;

  {
    /// load the shared library
    typedef FUNC_API_TYPE(DestroyAsset) DestroyAssetFuncPtr;
    DestroyAssetFuncPtr func_destroy_func_ptr = m_pLibraryManager->GetFunc<DestroyAssetFuncPtr>(m_oConfigAsset.GetLibraryFile(), TOSTRING(DestroyAsset));
    /// create the display with configure
    func_destroy_func_ptr(m_pAsset, m_oConfigAsset);
  }

  {
    /// load the shared library
    typedef FUNC_API_TYPE(DestroyFlash) DestroyFlashFuncPtr;
    DestroyFlashFuncPtr func_destroy_func_ptr = m_pLibraryManager->GetFunc<DestroyFlashFuncPtr>(m_oConfigFlash.GetLibraryFile(), TOSTRING(DestroyFlash));
    /// create the display with configure
    func_destroy_func_ptr(m_pFlash, m_oConfigFlash);
  }

  {
    /// load the shared library
    typedef FUNC_API_TYPE(DestroyScript) DestroyScriptFuncPtr;
    DestroyScriptFuncPtr func_destroy_func_ptr = m_pLibraryManager->GetFunc<DestroyScriptFuncPtr>(m_oConfigScript.GetLibraryFile(), TOSTRING(DestroyScript));
    /// create the display with configure
    func_destroy_func_ptr(m_pScript, m_oConfigScript);
  }

  delete m_pLibraryManager;
  m_pLibraryManager = NULL;

  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

bool CScene::Load(core::IRender* const& rpRender, const std::string& rsFileName, bool bIsAbsolutePath /*= false*/)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  //TODO:
  CAssetsBuilder::instance.BindRender(rpRender);

  std::string file_context = "";
  if (bIsAbsolutePath) file_context = utility::ReadFile(rsFileName);
  else file_context = utility::ReadFile(m_oConfig._sDataPath + "/" + rsFileName);
  rapidjson::Document jdoc;
  jdoc.Parse(file_context.c_str());
  CPanel::builder.Do(this, jdoc, m_pPanel);
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
  bool res = m_bNeedFlush;

  res |= m_pPanel->Tick(rfDelta);

  //TODO:
  //m_bNeedFlush = false;
  return res;
}

bool CScene::Draw(render::ICanvas* const& rpCanvas)
{
  for (int i = C4G_LAYER_MIN; i < C4G_LAYER_MAX; ++i)
  {
    if (m_pPanel->layer == i) m_pPanel->Draw(i, rpCanvas);
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
  if (rpInput->type == display::EInputType_Touch && rpInput->event == display::EInputEvent_Up)
  {
    if (!m_bPlayEffect)
    {
      m_pPanel->PlayEffect("p");
      m_bPlayEffect = true;
    }
    else
    {
      m_pPanel->PauseEffect();
      //m_pPanel->StopEffect();
      m_bPlayEffect = false;
    }
  }
  return res;
}

bool CScene::Refresh(const display::ISensor* const& rpSensor)
{
  bool res = false;
  for (int i = C4G_LAYER_MIN; i < C4G_LAYER_MAX; ++i)
  {
    res |= m_pPanel->Refresh(i, rpSensor);
  }
  return res;
}

core::IAsset* const& CScene::GetAssetPtr()
{
  return m_pAsset;
}

core::IFlash* const& CScene::GetFlashPtr()
{
  return m_pFlash;
}

void CScene::BindScript(script::AHandler* const& rpHandler)
{
  assert(NULL != m_pScript);
  m_pScript->New(rpHandler);
}

void CScene::SetDataPath(const std::string& rsDataPath)
{
  m_oConfig._sDataPath = rsDataPath;
}

const std::string& CScene::GetDataPath() const
{
  return m_oConfig._sDataPath;
}

IPanel* const& CScene::GetPanel()
{
  return m_pPanel;
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

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

namespace c4g {
namespace scene {

CScene::CScene()
  : m_pAsset(NULL)
  , m_pFlash(NULL)
  , m_pScript(NULL)
  , m_pPanel(NULL)
  , m_bNeedFlush(true)
  , m_bPlayEffect(false)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

CScene::~CScene()
{
  if (NULL != m_pPanel)
  {
    delete m_pPanel;
    m_pPanel = NULL;
  }

  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

bool CScene::Initialize(core::MString2Module& rmModule)
{
  m_pAsset = core::IModule::Find<core::IAsset>(rmModule, MODULE_TYPE_ASSET);
  m_pAsset->Initialize(rmModule);
  m_pFlash = core::IModule::Find<core::IFlash>(rmModule, MODULE_TYPE_FLASH);
  m_pFlash->Initialize(rmModule);
  m_pScript = core::IModule::Find<core::IScript>(rmModule, MODULE_TYPE_SCRIPT);
  m_pScript->Initialize(rmModule);

  if (NULL == m_pPanel)
  {
    m_pPanel = new CPanel(this, NULL);
    m_pPanel->layout.type = ELayoutType_Scale;
  }

  return true;
}

void CScene::SetDataPath(const std::string& rsDataPath)
{
  m_sDataPath = rsDataPath;
}

bool CScene::Load(core::IRender* const& rpRender, const std::string& rsFileName, bool bIsAbsolutePath /*= false*/)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);

  //TODO:
  CAssetsBuilder::instance.BindRender(rpRender);

  std::string file_context = "";
  if (bIsAbsolutePath) file_context = utility::ReadFile(rsFileName);
  else file_context = utility::ReadFile(std::string(*m_sDataPath) + "/" + rsFileName);
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

bool CScene::Draw(core::IRender* const& rpRender)
{
  assert(rpRender && rpRender->Canvas() && rpRender->Space());
  for (int i = C4G_LAYER_MIN; i < C4G_LAYER_MAX; ++i)
  {
    if (m_pPanel->layer == i) m_pPanel->Draw(i, rpRender->Canvas());
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

const char* const CScene::GetDataPath() const
{
  return *m_sDataPath;
}

IPanel* const& CScene::GetPanel()
{
  return m_pPanel;
}

}
}

bool CreateModule(c4g::core::IModule*& rpScene)
{
  assert(rpScene == NULL);
  if (NULL != rpScene) return false;
  rpScene = new c4g::scene::CScene();
  return true;
}

bool DestroyModule(c4g::core::IModule*& rpScene)
{
  assert(rpScene != NULL);
  if (NULL == rpScene) return false;
  delete rpScene;
  rpScene = NULL;
  return true;
}

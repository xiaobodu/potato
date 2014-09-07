#include <rapidjson/document.h>

#include "scene_impl.h"
#include "render.h"
#include "asset.h"

#include "utility/log.h"

#include <cassert>

namespace c4g {
namespace scene {

static unsigned char g_aiTexArray[4 * 4] = {
    0xFF, 0x00, 0x00, 0x38,
    0x00, 0xFF, 0x00, 0x38,
    0x00, 0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};
static render::Glyph g_Glyph;

CScene::CScene(const base::Config& roConfig)
  : m_pAsset(NULL)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

CScene::~CScene()
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
}

bool CScene::Load(core::IRender* const& rpRender, const std::string& rsFileName)
{
  C4G_LOG_INFO(__PRETTY_FUNCTION__);
  g_Glyph.l = 0.0f;
  g_Glyph.r = 5.0f;
  g_Glyph.t = 0.0f;
  g_Glyph.b = 5.0f;
  g_Glyph.id = rpRender->GenerateTexId(2, 2, g_aiTexArray);
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
  return true;
}

bool CScene::Handle(const display::IInput* const pInput)
{
  return true;
}

bool CScene::Tick(const float& rfDelta)
{
  return true;
}

bool CScene::Draw(render::ICanvas* const& rpCanvas)
{
  rpCanvas->DrawGlyph(g_Glyph, 300, 300, NULL);
  return true;
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

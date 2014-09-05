#include "scene_impl.h"
#include "asset.h"

#include <cassert>

namespace ac{
namespace scene{

CScene::CScene(const ac::base::Config& roConfig)
  : m_pAsset(NULL)
{
  ;
}

CScene::~CScene()
{
  ;
}

bool CScene::Load(const std::string& rsFileName)
{
  return true;
}

bool CScene::Resize(const int& riWidth, const int& riHeight)
{
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

bool CScene::Draw(const render::ICanvas* pCanvas)
{
  return true;
}

}
}

bool CreateScene(ac::core::IScene*& rpScene, const ac::base::Config& roConfig)
{
  assert(rpScene == NULL);
  if (NULL != rpScene)
  {
    return false;
  }
  rpScene = new ac::scene::CScene(roConfig);
  return true;
}

bool DestroyScene(ac::core::IScene*& rpScene, const ac::base::Config& roConfig)
{
  assert(rpScene != NULL);
  if (NULL == rpScene)
  {
    return false;
  }
  delete rpScene;
  rpScene = NULL;
  return true;
}

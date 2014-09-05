#include "scene.h"

#include <cassert>

bool CreateScene(ac::core::IScene*& rpScene, const ac::base::Config& roConfig)
{
  assert(rpScene == NULL);
  if (NULL != rpScene)
  {
    return false;
  }
  //rpScene = new ac::display::CScene(roConfig);
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

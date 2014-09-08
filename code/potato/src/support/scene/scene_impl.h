#pragma once

#include "scene.h"

namespace c4g {

namespace core {
class IAsset;
}
namespace utility{
class CSharedLibraryManager;
}

namespace scene {

class CScene : public core::IScene
{
public:
  explicit CScene(const base::Config& roConfig);
  virtual ~CScene();

public:
  virtual bool Load(core::IRender* const& rpRender, const std::string& rsFileName);
  virtual bool Unload(core::IRender* const& rpRender);
  virtual bool Resize(const int& riWidth, const int& riHeight);
  virtual bool Handle(const display::IInput* const pInput);
  virtual bool Tick(const float& rfDelta);
  virtual bool Draw(render::ICanvas* const& rpCanvas);

private:
  base::Config          m_oConfigAsset;
  core::IAsset*         m_pAsset;
  utility::CSharedLibraryManager* m_pLibraryManager;
};

}
}

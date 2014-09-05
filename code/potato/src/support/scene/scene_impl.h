#pragma once

#include "scene.h"

namespace ac{

namespace core{
class IAsset;
}

namespace scene{

class CScene : public core::IScene
{
public:
  explicit CScene(const ac::base::Config& roConfig);
  virtual ~CScene();

public:
  virtual bool Load(const std::string& rsFileName);
  virtual bool Resize(const int& riWidth, const int& riHeight);
  virtual bool Handle(const display::IInput* const pInput);
  virtual bool Tick(const float& rfDelta);
  virtual bool Draw(const render::ICanvas* pCanvas);

private:
  core::IAsset* m_pAsset;
};

}
}

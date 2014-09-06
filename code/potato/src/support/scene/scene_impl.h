#pragma once

#include "scene.h"

namespace c4g{

namespace core{
class IAsset;
}

namespace scene{

class CScene : public core::IScene
{
public:
  explicit CScene(const base::Config& roConfig);
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

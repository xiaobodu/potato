#pragma once

#include "common.h"

namespace ac{
namespace core{

class IScene;

class IRender
{
public:
  virtual ~IRender() { ; }

public:
  virtual void Start() = 0;
  virtual bool Resize(const int& riWidth, const int& riHeight) = 0;
  virtual bool Render(const float& rfDeltaTime, IScene* pScene) = 0;
  virtual void End() = 0;
};

}

namespace render{

class ICanvas
{
public:
  virtual ~ICanvas() { ; }

public:
};

}
}

FUNC_API_DECLARE(CreateRender, ac::core::IRender, const ac::base::Config);
FUNC_API_DECLARE(DestroyRender, ac::core::IRender, const ac::base::Config);

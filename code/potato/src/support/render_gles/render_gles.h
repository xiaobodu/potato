#pragma once

#include "common.h"

#include "render.h"

namespace ac{
namespace render{

class CRender : public core::IRender
{
public:
  CRender(const base::Config& roConfig);
  virtual ~CRender();

public:
  virtual void Start();
  virtual void Resize(int iWidth, int iHeight);
  virtual bool Tick(const double& rdDeltaS);
  virtual void End();

private:
  void Perspective(double fovy, double aspect, double near, double far);
};

}
}

FUNC_API_DECLARE(CreateRender, ac::core::IRender, const ac::base::Config);
FUNC_API_DECLARE(DestroyRender, ac::core::IRender, const ac::base::Config);

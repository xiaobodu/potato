#pragma once

#include "common.h"
#include "render.h"

namespace ac{
namespace render{
namespace gl{

class CRender : public core::IRender
{
public:
  CRender(const base::Config& roConfig);
  virtual ~CRender();

public:
  virtual void Start();
  virtual bool Tick(const double& rdDeltaS);
  virtual void Resize(int iWidth, int iHeight);
  virtual void End();

private:
  core::IDisplay* m_pDisplay;
};

}
}
}

FUNC_API_DECLARE(CreateRender, ac::core::IRender, const ac::base::Config);
FUNC_API_DECLARE(DestroyRender, ac::core::IRender, const ac::base::Config);

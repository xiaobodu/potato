#pragma once

#include "common.h"
#include "potato.h"

#include "display/display.h"
#include "render/render.h"

#include <string>

namespace ac{
namespace core{

class CEngine : public IEngine
{
public:
  CEngine(const ac::base::Config& roConfig);
  virtual ~CEngine();

public:
  virtual void Run();

private:
  base::Config m_oConfigDisplay;
  core::IDisplay* m_pDisplay;
  base::Config m_oConfigRender;
  core::IRender* m_pRender;
};

}
}

FUNC_API_DECLARE(CreateEngine, ac::core::IEngine, const ac::base::Config);
FUNC_API_DECLARE(DestroyEngine, ac::core::IEngine, const ac::base::Config);

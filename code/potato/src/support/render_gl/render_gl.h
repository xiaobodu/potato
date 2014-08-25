#pragma once

#include "common.h"
#include "render/render.h"

namespace ac{
namespace core{

class CRender : public IRender
{
public:
  CRender(const base::Config& roConfig);
  virtual ~CRender();

public:
};

}
}

FUNC_API_DECLARE(CreateRender, ac::core::IRender, const ac::base::Config);
FUNC_API_DECLARE(DestroyRender, ac::core::IRender, const ac::base::Config);

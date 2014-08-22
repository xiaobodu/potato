#pragma once

#include "common.h"
#include "potato.h"

#include <string>

FUNC_API_DECLARE(CreateEngine, ac::core::IEngine, const ac::base::Config);
FUNC_API_DECLARE(DestroyEngine, ac::core::IEngine, const ac::base::Config);

namespace ac{
namespace core{

class CEngine : public IEngine
{
public:
  CEngine(const ac::base::Config& roConfig);
  virtual ~CEngine();

public:
};

}
}

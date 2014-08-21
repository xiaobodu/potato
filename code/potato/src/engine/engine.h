#pragma once

#include "common.h"
#include "potato.h"

FUNC_API_DECLARE(CreateEngine, ac::core::IEngine);
FUNC_API_DECLARE(DestroyEngine, ac::core::IEngine);

namespace ac{
namespace core{

class CEngine : public IEngine
{
public:
  CEngine();
  virtual ~CEngine();

public:
};

}
}

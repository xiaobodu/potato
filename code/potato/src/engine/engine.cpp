#include "engine.h"

#include "utility/util_log.h"

#include <cassert>

bool CreateEngine(ac::core::IEngine*& rpEngine, const ac::base::Config& roConfig)
{
  assert(rpEngine == NULL);
  rpEngine = new ac::core::CEngine(roConfig);
  return true;
}

bool DestroyEngine(ac::core::IEngine*& rpEngine, const ac::base::Config& roConfig)
{
  assert(rpEngine != NULL);
  delete rpEngine;
  rpEngine = NULL;
  return true;
}

namespace ac{
namespace core{

CEngine::CEngine(const ac::base::Config& roConfig)
{
  utility::Log::Instance().TestAll();
  utility::Log::Instance().Info("call the 'CEngine' constructor");
}

CEngine::~CEngine()
{
  utility::Log::Instance().Info("call the 'CEngine' destructor");
}

}
}

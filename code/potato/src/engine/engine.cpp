#include "engine.h"

#include <cassert>

bool CreateEngine(ac::core::IEngine*& rpEngine)
{
  assert(rpEngine == NULL);
  rpEngine = new ac::core::CEngine;
  return true;
}

bool DestroyEngine(ac::core::IEngine*& rpEngine)
{
  assert(rpEngine != NULL);
  delete rpEngine;
  rpEngine = NULL;
  return true;
}

namespace ac{
namespace core{

CEngine::CEngine()
{
  ;
}

CEngine::~CEngine()
{
  ;
}

}
}

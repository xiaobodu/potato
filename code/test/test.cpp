#include "test.h"

#include <string>

#if !defined(ENGINE_FILE)
#error "can't find the engine dynamic library?"
#endif

int main(int argc, char* argv[])
{
  ac::core::IEngine*& engine = ac::Potato::Instance(ENGINE_FILE).GetEngine();
  return 0;
}

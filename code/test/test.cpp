#include "test.h"

#include <string>

#if !defined(ROOT_PATH)
#error "can't find the engine dynamic library?"
#endif

int main(int argc, char* argv[])
{
  ac::core::IEngine*& engine = ac::Potato::Instance(ROOT_PATH, "data/config.json").GetEngine();
  return 0;
}

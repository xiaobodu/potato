#include "test.h"

#include <string>

#if !defined(ENGINE_FILE)
# define ENGINE_FILE ""
#endif

int main(int argc, char* argv[])
{
  ac::core::IEngine*& engine = ac::Potato::Instance(ENGINE_FILE).GetEngine();
  return 0;
}

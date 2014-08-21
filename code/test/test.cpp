#include "test.h"

#include <string>

int main(int argc, char* argv[])
{
  ac::core::IEngine*& engine = ac::Potato::Instance("../lib/libengine.so").GetEngine();
  return 0;
}

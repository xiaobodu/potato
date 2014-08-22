#include "test.h"

#include <string>

#if !defined(ROOT_PATH)
#error "can't get the root path!!!"
#endif

void GetConfig(std::string& rsPath, std::string& rsFile)
{
  rsPath = ROOT_PATH;
  rsFile = "data/config.json";
}

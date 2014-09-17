#include "t001.h"

#include <string>

void GetConfig(std::string& rsLibrPath, std::string& rsDataPath, std::string& rsFile)
{
  rsLibrPath = LIBR_PATH;
  rsDataPath = DATA_PATH;
  rsFile = "potato.json";
}

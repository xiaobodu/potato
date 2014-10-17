#include "t001.h"

#include <string>

bool GetConfig(std::string& rsDataPath)
{
  rsDataPath = DATA_PATH;
  return true;
}

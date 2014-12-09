#include "demo.h"

#include <string>

bool GetConfig(TMapStr2Str& rmConfig)
{
  rmConfig.insert(std::make_pair("appname", APP_NAME));
  return true;
}

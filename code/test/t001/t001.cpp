#include "t001.h"

#include <string>

void GetConfig(std::string& rsLibrPath, std::string& rsDataPath, std::string& rsFile)
{
  rsLibrPath = LIBR_PATH;
  rsDataPath = DATA_PATH;
#if defined(OS_IS_LINUX)
  rsFile = "potato.json";
#elif defined(OS_IS_WINDOWS)
# if defined(BUILD_DEBUG)
  rsFile = "potato_windows_debug.json";
# elif defined(BUILD_MINSIZEREL)
  rsFile = "potato_windows_minsizerel.json";
# elif defined(BUILD_RELEASE)
  rsFile = "potato_windows_release.json";
# elif defined(BUILD_RELWITHDEBINFO)
  rsFile = "potato_windows_relwithdebinfo.json";
# else
  assert(0);
# endif
#endif
}

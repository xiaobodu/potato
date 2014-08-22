#pragma once

#include <fstream>
#include <sstream>

namespace ac{
namespace utility{

inline std::string ReadFile(const std::string& rsPathFile)
{
  std::ifstream fstr;
  fstr.open(rsPathFile.c_str(), std::ios_base::in);
  std::stringbuf file_context;
  fstr >> &file_context;
  return file_context.str();
}

}
}

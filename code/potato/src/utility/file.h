#pragma once

#include <fstream>
#include <sstream>

namespace c4g {
namespace utility {

inline std::string ReadFile(const std::string& rsPathFile)
{
  std::ifstream fstr;
  fstr.open(rsPathFile.c_str(), std::ios_base::in);
  std::stringbuf file_buffer;
  fstr >> &file_buffer;
  return file_buffer.str();
}

}
}

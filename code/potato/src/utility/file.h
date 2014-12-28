#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#if defined(CXX_GNU) || defined(CXX_CLANG)
#include <dirent.h>
#include <sys/stat.h>
#elif defined(CXX_MSVC)
#include <Windows.h>
#endif


namespace c4g {
namespace utility {

std::string ReadFile(const std::string& rsPathFile)
{
  std::ifstream fstr;
  fstr.open(rsPathFile.c_str(), std::ios_base::in);
  std::stringbuf file_buffer;
  fstr >> &file_buffer;
  return file_buffer.str();
}

bool GetListFiles(const std::string& rsPath, std::vector<std::string>& rsvFile, const std::string& rsFilter = "*")
{
#if defined(CXX_MSVC)
  HANDLE dir;
  WIN32_FIND_DATA file_data;

  if ((dir = FindFirstFile((rsPath + "/" + rsFilter).c_str(), &file_data)) == INVALID_HANDLE_VALUE)
  {
    return false; /* No files found */
  }

  do
  {
    const std::string file_name = file_data.cFileName;
    const std::string full_file_name = rsPath + "/" + file_name;
    const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

    if (file_name[0] == '.')
    {
      continue;
    }

    if (is_directory)
    {
      continue;
    }

    rsvFile.push_back(full_file_name);
  } while (FindNextFile(dir, &file_data));

  FindClose(dir);
#elif defined(CXX_GNU) || defined(CXX_CLANG)
  DIR* dir_ptr;
  struct dirent *ent;
  class stat st;

  dir_ptr = opendir(rsPath.c_str());
  while ((ent = readdir(dir_ptr)) != NULL)
  {
    const std::string file_name = ent->d_name;
    const std::string full_file_name = rsPath + "/" + file_name;

    if (file_name[0] == '.')
    {
      continue;
    }

    if (stat(full_file_name.c_str(), &st) == -1)
    {
      continue;
    }

    const bool is_directory = (st.st_mode & S_IFDIR) != 0;

    if (is_directory)
    {
      continue;
    }

    rsvFile.push_back(full_file_name);
  }
  closedir(dir_ptr);
#endif
  //DIR * dd;
  //class dirent *ent;
  //class stat st;
  return true;
}

}
}

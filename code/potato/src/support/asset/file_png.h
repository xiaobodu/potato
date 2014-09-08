#pragma once

#include "common.h"

namespace c4g {
namespace asset {

class CFilePNG
{
public:
  static CFilePNG& Instance();

private:
  CFilePNG();
  virtual ~CFilePNG();

public:
  void Load(const std::string& rsFileName);

public:
  const unsigned int& GetWidth() const;
  const unsigned int& GetHeight() const;
  unsigned char* GetBuffer() const;

private:
  void Free();

private:
  unsigned int m_iWidth;
  unsigned int m_iHeight;
  unsigned char* m_pBuffer;
};

}
}

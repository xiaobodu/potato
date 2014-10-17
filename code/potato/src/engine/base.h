#pragma once

#include "common.h"

namespace c4g {
namespace base {

typedef struct Glyph
{
  float l;
  float r;
  float t;
  float b;
  unsigned int id;

  Glyph()
      : l(0), r(0), t(0), b(0), id(0)
  {
    ;
  }
} SGlyph;

typedef struct Color
{
  typedef enum FlagBit
  {
    eFlagBit_None = 0x00,
    eFlagBit_R = 0x01,
    eFlagBit_G = 0x02,
    eFlagBit_B = 0x04,
    eFlagBit_A = 0x08,
  } EFlagBit;
  typedef unsigned char  Flags;

  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;

  Color()
    : r(0x00), g(0x00), b(0x00), a(0x00)
  {
    ;
  }
} SColor;

typedef struct Matrix
{
   float   m[4][4];
} SMatrix;

template<typename T>
class TScope
{
public:
  explicit TScope(T* const & rpT)
      : m_pT(rpT)
  {
    ;
  }

  virtual ~TScope()
  {
    ;
  }

protected:
  T* m_pT;
};

template<typename T>
class TPtrScope
{
public:
  explicit TPtrScope()
  {
    m_pT = NULL;
  }
  virtual ~TPtrScope()
  {
    Free();
  }

public:
  // just for pointer
  void operator=(T* const& rpT)
  {
    m_pT = rpT;
  }
  T* const& operator*()
  {
    return m_pT;
  }
  const T* const& operator*() const
  {
    return m_pT;
  }

protected:
  void Free()
  {
    if (NULL == m_pT) return;
    delete m_pT;
    m_pT = NULL;
  }

private:
  T* m_pT;
};

template<typename TKey>
class IValues
{
public:
  typedef TKey KeyType;

public:
  virtual ~IValues()
  {
    ;
  }

public:
  virtual IValues* const operator[](const TKey& rKey) = 0;
  virtual void operator=(const int& riValue) = 0;
  virtual void operator()(const TKey& rKey, int& riValue) const = 0;
  virtual void operator=(const float& rfValue) = 0;
  virtual void operator()(const TKey& rKey, float& rfValue) const = 0;
  virtual void operator=(const std::string& rsValue) = 0;
  virtual void operator()(const TKey& rKey, std::string& rsValue) const = 0;
};

}
}

FUNC_API_DECLARE(CreateModule, c4g::core::IModule);
FUNC_API_DECLARE(DestroyModule, c4g::core::IModule);

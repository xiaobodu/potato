#pragma once

#include "common.h"

namespace c4g {
namespace base {

struct Glyph
{
  float l;
  float r;
  float t;
  float b;
  unsigned int id;

  Glyph() : l(0), r(0), t(0), b(0), id(0) { ; }
};

template<typename T>
class TScope
{
public:
  explicit TScope(T* const& rpT)
    : m_pT(rpT)
  { ; }

  ~TScope()
  { ; }

protected:
  T* m_pT;
};

template<typename TKey>
class IValues
{
public:
  typedef TKey      KeyType;

public:
  virtual ~IValues() { ; }

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

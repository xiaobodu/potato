#pragma once

#include "common.h"

namespace c4g {
namespace base {

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

}
}

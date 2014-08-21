#pragma once

#include <cassert>
#include <cstring>

#if !defined(NULL)
# define NULL 0
#endif

namespace ac {
namespace tool {

class IEngine
{
public:
  virtual ~IEngine()
  {
    ;
  }

public:
};

}
}

extern "C" bool CreateEngine(ac::tool::IEngine*& rpEngine);
extern "C" bool DestroyEngine(ac::tool::IEngine*& rpEngine);

namespace ac {
namespace tool {

class CPotato
{
public:
  static CPotato& Instance()
  {
    static CPotato gs_potato;
    return gs_potato;
  }

public:
  inline IEngine*& GetEngine()
  {
    return m_pEngine;
  }

protected:
  CPotato() :
      m_pEngine(NULL), m_iError(0)
  {
    if (!CreateEngine(m_pEngine))
    {
      assert(0);
    }
  }

  virtual ~CPotato()
  {
    DestroyEngine(m_pEngine);
  }

public:
  int GetError()
  {
    return m_iError;
  }

private:
  int m_iError;
  IEngine* m_pEngine;
};

}
}

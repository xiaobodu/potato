#pragma once

#include "base.h"

#include <memory.h>

namespace c4g {
namespace base {

template<typename TBase, typename TKey, unsigned int max>
class TValues: public TBase
{
public:
  TValues()
  {
    memset(&m_Key, 0, sizeof(TKey));
    memset(m_afValue, 0, sizeof(float) * max);
    memset(m_aiValue, 0, sizeof(int) * max);
  }
  virtual ~TValues()
  {
    ;
  }

public:
  virtual IValues<TKey>* const operator[](const TKey& rKey)
  {
    m_Key = rKey;
    return this;
  }
  virtual void operator=(const int& riValue)
  {
    m_aiValue[m_Key] = riValue;
  }
  virtual void operator()(const TKey& riKey, int& riValue) const
  {
    riValue = m_aiValue[riKey];
  }
  virtual void operator=(const float& rfValue)
  {
    m_afValue[m_Key] = rfValue;
  }
  virtual void operator()(const TKey& riKey, float& rfValue) const
  {
    rfValue = m_afValue[riKey];
  }
  virtual void operator=(const std::string& rsValue)
  {
    m_asValue[m_Key] = rsValue;
  }
  virtual void operator()(const TKey& riKey, std::string& rsValue) const
  {
    rsValue = m_asValue[riKey];
  }

private:
  TKey m_Key;
  int m_aiValue[max];
  float m_afValue[max];
  std::string m_asValue[max];
};

}
}

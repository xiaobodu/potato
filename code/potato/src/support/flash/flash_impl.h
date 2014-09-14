#pragma once

#include "flash.h"

namespace c4g {
namespace flash {

class CFlash : public core::IFlash
{
public:
  CFlash(const c4g::base::Config& roConfig);
  virtual ~CFlash();

public:
};

}
}

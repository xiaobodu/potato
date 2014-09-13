#pragma once

#include "display.h"
#include "values.h"

namespace c4g {
namespace display {

class CSensor : public base::TValues<display::ISensor, unsigned char, 0xFF>
{
public:
  CSensor();
  virtual ~CSensor();

public:
};

}
}

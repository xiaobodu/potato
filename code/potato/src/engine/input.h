#pragma once

#include "display.h"
#include "values.h"

#define C4G_INPUT_KEY_TYPE     't'
#define C4G_INPUT_KEY_KEYCODE  'k'
#define C4G_INPUT_KEY_SERIAL   's'

#define C4G_INPUT_TOUCH_X   'x'
#define C4G_INPUT_TOUCH_Y   'y'
#define C4G_INPUT_TOUCH_L   'l'
#define C4G_INPUT_TOUCH_T   't'

namespace c4g {
namespace display{

class CInput : public base::TValues<display::IInput, unsigned char, 0xFF>
{
public:
  CInput();
  virtual ~CInput();

public:
};

}
}

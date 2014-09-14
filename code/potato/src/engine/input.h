#pragma once

#include "display.h"
#include "values.h"

#define C4G_INPUT_KEY_TYPE     't'
#define C4G_INPUT_KEY_KEYCODE  'k'
#define C4G_INPUT_KEY_SERIAL   's'

#define C4G_INPUT_TOUCH_COUNT               0
#define C4G_INPUT_TOUCH_DATA_START          1
#define C4G_INPUT_TOUCH_DATA_SIZE           10
#define C4G_INPUT_TOUCH_DATA_COUNT_MAX      10
#define C4G_INPUT_TOUCH_X                   C4G_INPUT_TOUCH_DATA_START + 0
#define C4G_INPUT_TOUCH_Y                   C4G_INPUT_TOUCH_DATA_START + 1
#define C4G_INPUT_TOUCH_LEFT                C4G_INPUT_TOUCH_DATA_START + 2
#define C4G_INPUT_TOUCH_TOP                 C4G_INPUT_TOUCH_DATA_START + 3
#define C4G_INPUT_TOUCH_PRESSURE            C4G_INPUT_TOUCH_DATA_START + 4
#define C4G_INPUT_TOUCH_SIZE                C4G_INPUT_TOUCH_DATA_START + 5

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

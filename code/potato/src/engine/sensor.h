#pragma once

#include "display.h"
#include "values.h"


#define C4G_SENSOR_VECTOR_X         0
#define C4G_SENSOR_VECTOR_Y         1
#define C4G_SENSOR_VECTOR_Z         2
#define C4G_SENSOR_ACCELERATION_X   3
#define C4G_SENSOR_ACCELERATION_Y   4
#define C4G_SENSOR_ACCELERATION_Z   5
#define C4G_SENSOR_MAGNETIC_X       6
#define C4G_SENSOR_MAGNETIC_Y       7
#define C4G_SENSOR_MAGNETIC_Z       8

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

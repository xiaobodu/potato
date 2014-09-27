#pragma once

#if defined(CXX_MSVC)
#include <Windows.h>
#endif

#define C4G_TIME_HOUR_PER_DAY             24
#define C4G_TIME_MINUTE_PER_HOUR          60
#define C4G_TIME_SECOND_PER_MINUTE        60
#define C4G_TIME_MSECOND_PER_SECOND       1000

namespace c4g {
namespace time {

#if defined(CXX_MSVC)
double ConvertTime(const SYSTEMTIME& time)
{
  return ((static_cast<double>(time.wDay) * C4G_TIME_HOUR_PER_DAY)
    * C4G_TIME_MINUTE_PER_HOUR + static_cast<double>(time.wMinute))
    * C4G_TIME_SECOND_PER_MINUTE + static_cast<double>(time.wSecond)
    + static_cast<double>(time.wMilliseconds) / C4G_TIME_MSECOND_PER_SECOND;
}
#endif

}
}

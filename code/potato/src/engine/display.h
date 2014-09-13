#pragma once

#include "common.h"
#include "base.h"

namespace c4g {
namespace core {

class IScene;

class IDisplay
{
public:
  virtual ~IDisplay()
  {
    ;
  }

public:
#if defined(BUILD_ANDROID)
  virtual void BindAndroidApp(struct android_app* pApp) = 0;
#endif
  virtual void Run(core::IScene* const& rpScene) = 0;
};

} // end of namespace core

namespace display {

enum EInputType
{
  EInputType_None,
  EInputType_Key,
  EInputType_Touch,
};

enum EInputEvent
{
  EInputEvent_None,
  EInputEvent_Down,
  EInputEvent_Up,
  EInputEvent_Move,
};

class IInput : public base::IValues<unsigned char>
{
public:
  EInputType type;
  EInputEvent event;

public:
  virtual ~IInput()
  {
    ;
  }

public:
};

class ISensor : public base::IValues<unsigned char>
{
public:
  virtual ~ISensor()
  {
    ;
  }

public:
};

} // end of namespace display
} // end of namespace c4g

FUNC_API_DECLARE(CreateDisplay, c4g::core::IDisplay, const c4g::base::Config);
FUNC_API_DECLARE(DestroyDisplay, c4g::core::IDisplay, const c4g::base::Config);

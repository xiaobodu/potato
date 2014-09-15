#pragma once

#include "scene.h"
#include "utility/mathematics.h"

#include <string>
#include <vector>
#include <cassert>

#define C4G_LAYER_MAX           10
#define C4G_LAYER_MIN           0

namespace c4g {

namespace core {
class IAsset;
class IFlash;
}
namespace display {
class IInput;
class ISensor;
}
namespace render {
class ICanvas;
}
namespace flash {
class IEffect;
}
namespace script {
class AHandler;
}
namespace scene {

class ISceneImpl : public core::IScene
{
public:
  virtual ~ISceneImpl() { ; }

public:
  virtual core::IAsset* const& GetAssetPtr() = 0;
  virtual core::IFlash* const& GetFlashPtr() = 0;

  /// script
public:
  virtual void BindScript(script::AHandler* const& rpHandler) = 0;
};

class IResizable
{
public:
  virtual ~IResizable()
  {
    ;
  }

public:
  virtual void Resize(const float& rfWidth, const float& rfHeight) = 0;
};

class ITickable
{
public:
  virtual ~ITickable()
  {
    ;
  }

public:
  virtual bool Tick(const float& rfDelta) = 0;
};

class IDrawable
{
public:
  virtual ~IDrawable()
  {
    ;
  }

public:
  virtual void Draw(const int& riLayer, render::ICanvas* const & rpCanvas) = 0;
};

class IHandleable
{
public:
  virtual ~IHandleable()
  {
    ;
  }

public:
  virtual bool Handle(const int& riLayer, const display::IInput* const & rpInput) = 0;
};

class IRefreshable
{
public:
  virtual ~IRefreshable()
  {
    ;
  }

public:
  virtual bool Refresh(const int& riLayer, const display::ISensor* const & rpSensor) = 0;
};

class IDeal;

class IWidget : public IResizable, public ITickable, public IDrawable, public IHandleable, public IRefreshable
{
public:
  std::string id;
  int layer;
  bool resize;
  bool always_tick;
  bool visible;
  bool input;
  bool sensor;
  RectF dst;
  RectF dst_config;
  ISceneImpl* const scene;
  IWidget* parent;

public:
  explicit IWidget(ISceneImpl* const& rpScene, IWidget* const& rpParent)
    : id("unknown")
    , layer(0)
    , resize(false)
    , always_tick(false)
    , visible(false)
    , input(false)
    , sensor(false)
    , dst(0.0f)
    , dst_config(0.0f)
    , scene(rpScene)
    , parent(rpParent)
  {
    assert(NULL != rpScene);
  }
  virtual ~IWidget()
  {
    ;
  }

public:
  virtual void Add(IWidget* const& rpWidget) = 0;
  // deal the removed widget, delete or move or etc.
  virtual void Remove(const std::string& rsId, IDeal* const& rpDeal) = 0;
  virtual void Clear() = 0;
  virtual int Find(const std::string& rsId) const = 0;
  virtual IWidget* Get(const int& riIndex) = 0;

public:
  class IVisitor
  {
  public:
    virtual ~IVisitor() { ; }

  public:
    virtual void On(IWidget* const& rpWidget) const = 0;
  };
  virtual void Visit(IVisitor* const& rpVisitor) = 0;

  /// effect
public:
  virtual void PushEffect(const std::string& rsName, flash::IEffect* const& rpEffect) = 0;
  virtual flash::IEffect* const CurrentEffect() = 0;
  virtual void PlayEffect(const std::string& rsName, const bool& rbForce = false) = 0;
  virtual void StopEffect() = 0;
  virtual void PauseEffect() = 0;
  virtual void ContinueEffect() = 0;
};

typedef std::vector<IWidget*> VWidgetPtr;

class IDeal
{
public:
  virtual ~IDeal() { ; }

public:
  virtual void On(IWidget*& rpWidget) const = 0;
};


}
}

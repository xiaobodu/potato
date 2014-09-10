#pragma once

#include <string>
#include <vector>
#include <cassert>

#include "math.h"

#define C4G_LAYER_MAX           10
#define C4G_LAYER_MIN           0

namespace c4g {

namespace core {
class IScene;
}
namespace display {
class IInput;
}
namespace render {
class ICanvas;
}
namespace scene {

class IResizable
{
public:
  virtual ~IResizable()
  {
    ;
  }

public:
  virtual void Resize(const int& riWidth, const int& riHeight) = 0;
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

class IDeal;

class IWidget : public IResizable, public ITickable, public IDrawable, public IHandleable
{
public:
  std::string id;
  int layer;
  bool visible;
  bool always_tick;
  RectF dst;
  core::IScene* const scene;
  IWidget* parent;

public:
  explicit IWidget(core::IScene* const& rpScene, IWidget* const& rpParent)
    : id("unknown")
    , layer(0)
    , visible(false)
    , always_tick(false)
    , dst(0.0f)
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

#pragma once

#include <string>
#include <vector>

#include "math.h"

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
  virtual void Draw(render::ICanvas* const & rpCanvas) = 0;
};

class IHandleable
{
public:
  virtual ~IHandleable()
  {
    ;
  }

public:
  virtual bool Handle(const display::IInput* const & rpInput) = 0;
};

class IWidget : public IResizable, public ITickable, public IDrawable, public IHandleable
{
public:
  std::string id;
  int layer;
  bool visible;
  RectF dst;

public:
  IWidget()
    : id("unknown")
    , layer(0)
    , visible(false)
    , dst(0.0)
  {
    ;
  }
  virtual ~IWidget()
  {
    ;
  }

public:
  virtual core::IScene* const& Scene() = 0;
  virtual const IWidget* const Parent() const = 0;
  virtual void Add(IWidget* const& rpWidget) = 0;
  virtual IWidget* Remove(const std::string& rsId) = 0;
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

}
}

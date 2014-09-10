#pragma once

#include "widget.h"

namespace c4g {
namespace scene {

class IPanel : public IWidget
{
public:
  IPanel()
    : IWidget()
  {
    ;
  }
  virtual ~IPanel()
  {
    ;
  }

public:
};

class CPanel : public TWidget<IPanel>
{
public:
  explicit CPanel(core::IScene* const& rpScene, IWidget* const& rpParent);
  virtual ~CPanel();

public:
  virtual void Resize(const int& riWidth, const int& riHeight);
  virtual bool Tick(const float& rfDelta);
  virtual void Draw(render::ICanvas* const & rpCanvas);
  virtual bool Handle(const display::IInput* const& rpInput);

public:
  class CBuilder : public TBuilder<IPanel* const>
  {
  public:
    explicit CBuilder() : TBuilder<IPanel* const>("panel")
    {
      ;
    }
  public:
    virtual bool Parser(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, IPanel* const& rpPanel) const;
  };
  static CBuilder builder;
};

}
}

#pragma once

#include "widget.h"

namespace c4g {
namespace scene {

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
  class CBuilder : public TWidget<IPanel>::CBuilder
  {
  public:
    virtual bool Parser(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, IPanel* const& rpPanel) const;
  };
  static CBuilder builder;
};

}
}

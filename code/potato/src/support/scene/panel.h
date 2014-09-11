#pragma once

#include "widget.h"
#include "layout.h"

namespace c4g {
namespace scene {

class CEffect;

class IPanel : public IWidget
{
public:
  CLayout layout;

public:
  IPanel(core::IScene* const& rpScene, IWidget* const& rpParent)
    : IWidget(rpScene, rpParent)
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
  virtual void Resize(const float& rfWidth, const float& rfHeight);
  virtual bool Tick(const float& rfDelta);
  virtual void Draw(const int& riLayer, render::ICanvas* const & rpCanvas);
  virtual bool Handle(const int& riLayer, const display::IInput* const& rpInput);

private:
  CEffect* m_pEffect;

public:
  class CBuilder : public TBuilder<IPanel* const>
  {
  public:
    explicit CBuilder() : TBuilder<IPanel* const>("panel")
    {
      ;
    }
  public:
    virtual bool Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, IPanel* const& rpPanel) const;
  };
  static CBuilder builder;
};

}
}

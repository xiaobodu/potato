#pragma once

#include "widget.h"

namespace c4g {
namespace scene {

class CEffect;

class IImage : public IWidget
{
public:
  explicit IImage(ISceneWithScript* const& rpScene, IWidget* const& rpParent)
    : IWidget(rpScene, rpParent)
  {
    ;
  }
  virtual ~IImage()
  {
    ;
  }

public:
  render::Glyph src;
};

class CImage : public TWidget<IImage>
{
public:
  explicit CImage(ISceneWithScript* const& rpScene, IWidget* const& rpParent);
  virtual ~CImage();

public:
  virtual bool Tick(const float& rfDelta);
  virtual void Draw(const int& riLayer, render::ICanvas* const & rpCanvas);
  /*virtual bool Handle(const int& riLayer, const display::IInput* const& rpInput);
  virtual bool Refresh(const int& riLayer, const display::ISensor* const & rpSensor);*/

public:
  class CBuilder : public TBuilder<CImage* const>
  {
  public:
    explicit CBuilder() : TBuilder<CImage* const>("image")
    {
      ;
    }
  public:
    virtual bool Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, CImage* const& rpImage) const;
  };
  static CBuilder builder;
  friend class CBuilder;

private:
  CEffect* m_pEffect;
};

}
}

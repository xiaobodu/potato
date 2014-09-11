#pragma once

#include "widget.h"

namespace c4g {
namespace scene {

class CEffect;

class IImage : public IWidget
{
public:
  explicit IImage(core::IScene* const& rpScene, IWidget* const& rpParent)
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
  explicit CImage(core::IScene* const& rpScene, IWidget* const& rpParent);
  virtual ~CImage();

public:
  virtual void Resize(const float& rfWidth, const float& rfHeight);
  virtual bool Tick(const float& rfDelta);
  virtual void Draw(const int& riLayer, render::ICanvas* const & rpCanvas);
  virtual bool Handle(const int& riLayer, const display::IInput* const& rpInput);

public:
  class CBuilder : public TBuilder<IImage* const>
  {
  public:
    explicit CBuilder() : TBuilder<IImage* const>("image")
    {
      ;
    }
  public:
    virtual bool Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, IImage* const& rpImage) const;
  };
  static CBuilder builder;

private:
  CEffect* m_pEffect;
};

}
}

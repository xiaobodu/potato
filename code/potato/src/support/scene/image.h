#pragma once

#include "widget.h"

namespace c4g {
namespace scene {

class CProcess;

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
  base::Glyph src;
};

class CImage : public TWidget<IImage>
{
public:
  explicit CImage(ISceneWithScript* const& rpScene, IWidget* const& rpParent);
  virtual ~CImage();

public:
  virtual bool Tick(const float& rfDelta);
  virtual void Draw(const int& riLayer, render::ICanvas* const & rpCanvas);

public:
  class CBuilder : public TBuilder<CImage* const>
  {
  public:
    explicit CBuilder();

  public:
    virtual bool Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, CImage* const& rpImage) const;
  };
  static CBuilder builder;

private:
  CProcess* m_pProcess;
};

}
}

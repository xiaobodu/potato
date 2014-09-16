#pragma once

#include "widget.h"

namespace c4g {
namespace scene {

class CProcess;

class IImage : public IWidget
{
public:
  explicit IImage(ISceneImpl* const& rpScene, IWidget* const& rpParent)
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
  explicit CImage(ISceneImpl* const& rpScene, IWidget* const& rpParent);
  virtual ~CImage();

public:
  virtual bool Tick(const float& rfDelta);
  virtual void Draw(const int& riLayer, render::ICanvas* const & rpCanvas);

private:
  CProcess* m_pProcess;

public:
  class CBuilder : public TBuilder<CImage* const>
  {
  public:
    explicit CBuilder();

  public:
    virtual bool Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, CImage* const& rpImage) const;
  };
  static CBuilder builder;
};

}
}

#pragma once

#include "widget.h"

#include "render.h"

namespace c4g {
namespace scene {

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
  virtual void BuildEnd() = 0;

public:
  render::Glyph src;
};

class CImage : public TWidget<IImage>
{
public:
  explicit CImage(core::IScene* const& rpScene, IWidget* const& rpParent);
  virtual ~CImage();

public:
  virtual void Resize(const int& riWidth, const int& riHeight);
  virtual bool Tick(const float& rfDelta);
  virtual void Draw(const int& riLayer, render::ICanvas* const & rpCanvas);
  virtual bool Handle(const int& riLayer, const display::IInput* const& rpInput);

public:
  virtual void BuildEnd();

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
  class CProcess : public render::IProcess
  {
  public:
    CProcess() : m_fX(0.0f), m_fY(0.0f), m_fAngle(0.0f) { ; }
    virtual ~CProcess() { ; }

  public:
    void SetPos(const float& rfX, const float& rfY)
    {
      m_fX = rfX;
      m_fY = rfY;
    }

  public:
    virtual void Begin(const render::Glyph& rGlyph) { ; }
    virtual bool Do(render::ITransform* const& rpTransform)
    {
      // think in the 3d transform
      rpTransform->Translate(m_fX, m_fY);
      rpTransform->Rotate(m_fAngle, 0.0f, 0.0f, 1.0f, 0, 0, 0.0f);
      return true;
    }
    virtual void End() { ; }

  public:
    bool Tick(const float& rfDelta)
    {
      m_fAngle += rfDelta * 200.0f;
      if (m_fAngle > 360.0f) m_fAngle-= 360.0f;
      return true;
    }

  private:
    float m_fX;
    float m_fY;
    float m_fAngle;
  };
  CProcess* m_pProcess;
};

}
}

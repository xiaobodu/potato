#include "image.h"

#include "scene.h"
#include "effect.h"

#include <cassert>

namespace c4g {
namespace scene {

CImage::CBuilder CImage::builder;

CImage::CImage(core::IScene* const& rpScene, IWidget* const& rpParent)
  : TWidget<IImage>(rpScene, rpParent)
  , m_pEffect(NULL)
{
  m_pEffect = new CEffect();
}

CImage::~CImage()
{
  delete m_pEffect;
  m_pEffect = NULL;
}

void CImage::Resize(const float& rfWidth, const float& rfHeight)
{
  ;
}

bool CImage::Tick(const float& rfDelta)
{
  return m_pEffect->Tick(rfDelta);
}

void CImage::Draw(const int& riLayer, render::ICanvas* const & rpCanvas)
{
  m_pEffect->SetPos(dst.l, dst.t);
  rpCanvas->DrawGlyph(src, dst.w, dst.h, m_pEffect);
  //
}

bool CImage::Handle(const int& riLayer, const display::IInput* const & rpInput)
{
  //
  return true;
}

bool CImage::CBuilder::Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, IImage* const & rpImage) const
{
  const rapidjson::Value& jvalue = roConfig["value"];
  assert(jvalue.IsObject());
  if (!jvalue.IsObject()) return false;

  if (!CWidgetBuilder::instance.Do(rpAsset, jvalue, rpImage))
  {
    return false;
  }

  const rapidjson::Value& jsrc = jvalue["src"];
  assert(jsrc.IsObject());
  if (!jsrc.IsObject()) return false;

  if (!CGlyphBuilder::instance.Do(rpAsset, jsrc, rpImage->src))
  {
    return false;
  }

  return true;
}

}
}

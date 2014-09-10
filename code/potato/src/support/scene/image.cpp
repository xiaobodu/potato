#include "image.h"

#include "scene.h"

namespace c4g {
namespace scene {

CImage::CBuilder CImage::builder;

CImage::CImage(core::IScene* const& rpScene, IWidget* const& rpParent)
  : TWidget<IImage>(rpScene, rpParent)
{
  ;
}

CImage::~CImage()
{
  ;
}

void CImage::Resize(const int& riWidth, const int& riHeight)
{
  //
}

bool CImage::Tick(const float& rfDelta)
{
  //
  return true;
}

void CImage::Draw(const int& riLayer, render::ICanvas* const & rpCanvas)
{
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

  //TODO:
  return true;
}

}
}

#include "image.h"

#include "scene.h"

namespace c4g {
namespace scene {

CImage::CBuilder CImage::builder;

CImage::CImage(core::IScene* const& rpScene, IWidget* const& rpParent)
  : TWidget<IImage>(rpScene, rpParent)
  , m_pProcess(NULL)
{
  m_pProcess = new CImage::CProcess();
}

CImage::~CImage()
{
  delete m_pProcess;
  m_pProcess = NULL;
}

void CImage::Resize(const int& riWidth, const int& riHeight)
{
  //
}

bool CImage::Tick(const float& rfDelta)
{
  return m_pProcess->Tick(rfDelta);
}

void CImage::Draw(const int& riLayer, render::ICanvas* const & rpCanvas)
{
  rpCanvas->DrawGlyph(src, dst.w, dst.h, m_pProcess);
  //
}

bool CImage::Handle(const int& riLayer, const display::IInput* const & rpInput)
{
  //
  return true;
}

void CImage::BuildEnd()
{
  m_pProcess->SetPos(dst.l, dst.t);
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
  rpImage->BuildEnd();
  return true;
}

}
}

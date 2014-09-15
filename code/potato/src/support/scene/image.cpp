#include "image.h"

#include "scene.h"
#include "process.h"

#include "utility/log.h"

#include <cassert>

namespace c4g {
namespace scene {

CImage::CBuilder CImage::builder;

CImage::CImage(ISceneImpl* const& rpScene, IWidget* const& rpParent)
  : TWidget<IImage>(rpScene, rpParent)
  , m_pProcess(NULL)
  , m_runeffect(false)
{
  m_pProcess = new CProcess(this);
}

CImage::~CImage()
{
  delete m_pProcess;
  m_pProcess = NULL;
}

// for script
typedef bool (*script_image_tick)(float fDelta);
bool script_image_tick_default(float fDelta)
{
  //utility::Log::Instance().Warning("missing 'tick' function in script");
  return false;
}

bool CImage::Tick(const float& rfDelta)
{
  if (!m_runeffect)
  {
    PlayEffect("r");
    m_runeffect = true;
  }

  // call script
  bool res = CallScript<script_image_tick>("tick", script_image_tick_default)(rfDelta);

  res |= CurrentEffect()->Tick(rfDelta);
  return res;
}

// for script
typedef void (*script_image_draw)(int iLayer);
void script_image_draw_default(int iLayer)
{
  //utility::Log::Instance().Warning("missing 'draw' function in script");
}

void CImage::Draw(const int& riLayer, render::ICanvas* const & rpCanvas)
{
  // call script
  CallScript<script_image_draw>("draw", script_image_draw_default)(riLayer);

  m_pProcess->SetPos(dst.l, dst.t);
  rpCanvas->DrawGlyph(src, dst.w, dst.h, m_pProcess);
}


CImage::CBuilder::CBuilder()
  : TBuilder<CImage* const>("image")
{
  ;
}

bool CImage::CBuilder::Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, CImage* const & rpImage) const
{
  const rapidjson::Value& jvalue = roConfig["value"];
  assert(jvalue.IsObject());
  if (!jvalue.IsObject()) return false;

  if (!CWidgetBuilder::instance.Do(rpScene, jvalue, rpImage))
  {
    return false;
  }

  const rapidjson::Value& jsrc = jvalue["src"];
  assert(jsrc.IsObject());
  if (!jsrc.IsObject()) return false;

  if (!CGlyphBuilder::instance.Do(rpScene, jsrc, rpImage->src))
  {
    return false;
  }

  if (jvalue.HasMember("script"))
  {
    const rapidjson::Value& jscript = jvalue["script"];
    CScriptBuilder::instance.Do(rpScene, jscript, rpImage->m_pSubstance);
  }

  return true;
}

}
}

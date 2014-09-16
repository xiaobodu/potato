#include "flip.h"

#include "scene.h"
#include "process.h"

#include "utility/log.h"

#include <cassert>

namespace c4g {
namespace scene {

CFlip::CBuilder CFlip::builder;

CFlip::CFlip(ISceneImpl* const& rpScene, IWidget* const& rpParent)
  : TWidget<IFlip>(rpScene, rpParent)
  , m_pProcess(NULL)
  , m_bPlay(false)
  , m_fFlipTime(0.0f)
{
  m_pProcess = new CProcess(this);
}

CFlip::~CFlip()
{
  delete m_pProcess;
  m_pProcess = NULL;
}

// for script
typedef bool (*script_flip_tick)(float fDelta);
bool script_flip_tick_default(float fDelta)
{
  //utility::Log::Instance().Warning("missing 'tick' function in script");
  return false;
}

bool CFlip::Tick(const float& rfDelta)
{
  // call script
  bool res = CallScript<script_flip_tick>("tick", script_flip_tick_default)(rfDelta);

  res = CurrentEffect()->Tick(rfDelta) || res;
  res = NextIndex(rfDelta) || res;
  return res;
}

// for script
typedef void (*script_flip_draw)(int iLayer);
void script_flip_draw_default(int iLayer)
{
  //utility::Log::Instance().Warning("missing 'draw' function in script");
}

void CFlip::Draw(const int& riLayer, render::ICanvas* const & rpCanvas)
{
  // call script
  CallScript<script_flip_draw>("draw", script_flip_draw_default)(riLayer);

  m_pProcess->SetPos(dst.l, dst.t);
  rpCanvas->DrawGlyph(srcs[index], dst.w, dst.h, m_pProcess);
}

void CFlip::Play()
{
  m_bPlay = true;
}

void CFlip::Stop()
{
  m_bPlay = false;
  m_fFlipTime = 0.0f;
  index = 0;
}

void CFlip::Pause()
{
  m_bPlay = false;
}

void CFlip::Continue()
{
  m_bPlay = true;
}

bool CFlip::NextIndex(const float& rfDelta)
{
  if (!m_bPlay || 0 >= speed) return false;

  m_fFlipTime += rfDelta;
  int delta_index = static_cast<int>(m_fFlipTime / speed);
  int current_index = index;
  m_fFlipTime -= delta_index * speed;
  index = (index + delta_index) % static_cast<int>(srcs.size());
  return (current_index != index);
}

CFlip::CBuilder::CBuilder()
  : TBuilder<CFlip* const>("flip")
{
  ;
}

bool CFlip::CBuilder::Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, CFlip* const & rpFlip) const
{
  const rapidjson::Value& jvalue = roConfig["value"];
  assert(jvalue.IsObject());
  if (!jvalue.IsObject()) return false;

  if (!CWidgetBuilder::instance.Do(rpScene, jvalue, rpFlip))
  {
    return false;
  }

  const rapidjson::Value& jsrcs = jvalue["srcs"];
  assert(jsrcs.IsArray());
  if (!jsrcs.IsArray()) return false;

  if (!CGlyphListBuilder::instance.Do(rpScene, jsrcs, rpFlip->srcs))
  {
    return false;
  }

  if (jvalue.HasMember("script"))
  {
    const rapidjson::Value& jscript = jvalue["script"];
    CScriptBuilder::instance.Do(rpScene, jscript, rpFlip->m_pSubstance);
  }

  return true;
}

}
}

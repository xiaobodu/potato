#include "panel.h"

#include "scene.h"

namespace c4g {
namespace scene {

CPanel::CBuilder CPanel::builder;

CPanel::CPanel(core::IScene* const& rpScene, IWidget* const& rpParent)
  : TWidget<IPanel>(rpScene, rpParent)
{
  ;
}

CPanel::~CPanel()
{
  ;
}

void CPanel::Resize(const int& riWidth, const int& riHeight)
{
  //
}

bool CPanel::Tick(const float& rfDelta)
{
  //
  return true;
}

void CPanel::Draw(render::ICanvas* const & rpCanvas)
{
  //
}

bool CPanel::Handle(const display::IInput* const & rpInput)
{
  //
  return true;
}

bool CPanel::CBuilder::Parser(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, IPanel* const & rpPanel) const
{
  const rapidjson::Value& jtype = roConfig["type"];
  assert(jtype.IsString());
  if (!jtype.IsString()) return false;
  if (name != jtype.GetString()) return false;

  const rapidjson::Value& jvalue = roConfig["value"];
  assert(jvalue.IsObject());
  if (!jvalue.IsObject()) return false;

  if (!CWidgetBuilder::instance.Parser(rpAsset, jvalue, rpPanel))
  {
    return false;
  }

  //TODO:
  return true;
}

}
}

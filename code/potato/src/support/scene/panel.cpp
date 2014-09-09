#include "panel.h"

#include "scene.h"

namespace c4g {
namespace scene {

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
  if (!TWidget<IPanel>::CBuilder::Parser(rpAsset, roConfig, rpPanel))
  {
    return false;
  }

  //TODO:
  return true;
}

CPanel::CBuilder CPanel::builder;

}
}

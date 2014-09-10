#include "panel.h"

#include "scene.h"
#include "image.h"

namespace c4g {
namespace scene {

CPanel::CBuilder CPanel::builder;

CPanel::CPanel(core::IScene* const & rpScene, IWidget* const & rpParent)
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
  VWidgetPtr::iterator it = m_vpWidget.begin();
  VWidgetPtr::iterator it_end = m_vpWidget.end();
  for (; it != it_end; ++it)
  {
    IWidget*& widget_ptr = *it;
    widget_ptr->Resize(riWidth, riHeight);
  }
}

bool CPanel::Tick(const float& rfDelta)
{
  bool res = false;
  VWidgetPtr::iterator it = m_vpWidget.begin();
  VWidgetPtr::iterator it_end = m_vpWidget.end();
  for (; it != it_end; ++it)
  {
    IWidget*& widget_ptr = *it;
    if (widget_ptr->always_tick || widget_ptr->visible) res |= widget_ptr->Tick(rfDelta);
  }
  //TEST:
  return res;
  //return true;
}

void CPanel::Draw(const int& riLayer, render::ICanvas* const & rpCanvas)
{
  VWidgetPtr::iterator it = m_vpWidget.begin();
  VWidgetPtr::iterator it_end = m_vpWidget.end();
  for (; it != it_end; ++it)
  {
    IWidget*& widget_ptr = *it;
    if (widget_ptr->visible && riLayer == widget_ptr->layer) widget_ptr->Draw(riLayer, rpCanvas);
  }
}

bool CPanel::Handle(const int& riLayer, const display::IInput* const & rpInput)
{
  bool res = false;
  VWidgetPtr::iterator it = m_vpWidget.begin();
  VWidgetPtr::iterator it_end = m_vpWidget.end();
  for (; it != it_end; ++it)
  {
    IWidget*& widget_ptr = *it;
    if (widget_ptr->visible && riLayer == widget_ptr->layer) res |= widget_ptr->Handle(riLayer, rpInput);
  }
  return res;
}

bool CPanel::CBuilder::Do(core::IAsset* const & rpAsset, const rapidjson::Value& roConfig, IPanel* const & rpPanel) const
{
  const rapidjson::Value& jtype = roConfig["type"];
  assert(jtype.IsString());
  if (!jtype.IsString()) return false;
  if (name != jtype.GetString()) return false;

  const rapidjson::Value& jvalue = roConfig["value"];
  assert(jvalue.IsObject());
  if (!jvalue.IsObject()) return false;

  if (!CWidgetBuilder::instance.Do(rpAsset, jvalue, rpPanel))
  {
    return false;
  }

  const rapidjson::Value& jassets = jvalue["assets"];
  if (!CAssetsBuilder::instance.Do(rpAsset, jassets, NULL))
  {
    return false;
  }

  const rapidjson::Value& jwidgets = jvalue["widgets"];
  assert(jwidgets.IsArray());
  if (!jwidgets.IsArray()) return false;

  for (int i = 0; i < static_cast<int>(jwidgets.Size()); ++i)
  {
    const rapidjson::Value& jwidget = jwidgets[i];
    if (!jwidget.IsObject()) continue;

    CAllWidgetBuilder::instance.Do(rpAsset, jwidget, rpPanel);
  }

  //TODO:
  return true;
}

}
}

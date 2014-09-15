#include "panel.h"

#include "scene.h"
#include "image.h"
#include "layout.h"
#include "process.h"

#include "input.h"
#include "sensor.h"

namespace c4g {
namespace scene {

CPanel::CBuilder CPanel::builder;

CPanel::CPanel(ISceneWithScript* const & rpScene, IWidget* const & rpParent)
  : TWidget<IPanel>(rpScene, rpParent)
  , m_pProcess(NULL)
{
  resize = true;
  input = true;
  sensor = true;

  m_pProcess = new CProcess();
}

CPanel::~CPanel()
{
  delete m_pProcess;
  m_pProcess = NULL;
}

void CPanel::Resize(const float& rfWidth, const float& rfHeight)
{
  VWidgetPtr::iterator it = m_vpWidget.begin();
  VWidgetPtr::iterator it_end = m_vpWidget.end();
  for (; it != it_end; ++it)
  {
    IWidget*& widget_ptr = *it;
    layout.Resize(dst_config, dst, widget_ptr);
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
  return res;
}

void CPanel::Draw(const int& riLayer, render::ICanvas* const & rpCanvas)
{
  m_pProcess->SetPos(dst.l, dst.t);
  rpCanvas->EffectBegin(m_pProcess);

  VWidgetPtr::iterator it = m_vpWidget.begin();
  VWidgetPtr::iterator it_end = m_vpWidget.end();
  for (; it != it_end; ++it)
  {
    IWidget*& widget_ptr = *it;
    if (widget_ptr->visible && riLayer == widget_ptr->layer) widget_ptr->Draw(riLayer, rpCanvas);
  }

  rpCanvas->EffectEnd(m_pProcess);
}

bool CPanel::Handle(const int& riLayer, const display::IInput* const & rpInput)
{
  bool res = false;
  VWidgetPtr::iterator it = m_vpWidget.begin();
  VWidgetPtr::iterator it_end = m_vpWidget.end();
  for (; it != it_end; ++it)
  {
    IWidget*& widget_ptr = *it;
    if (widget_ptr->input && widget_ptr->visible && riLayer == widget_ptr->layer) res |= widget_ptr->Handle(riLayer, rpInput);
  }
  return res;
}

bool CPanel::Refresh(const int& riLayer, const display::ISensor* const & rpSensor)
{
  bool res = false;
  VWidgetPtr::iterator it = m_vpWidget.begin();
  VWidgetPtr::iterator it_end = m_vpWidget.end();
  for (; it != it_end; ++it)
  {
    IWidget*& widget_ptr = *it;
    if (widget_ptr->sensor && widget_ptr->visible && riLayer == widget_ptr->layer) res |= widget_ptr->Refresh(riLayer, rpSensor);
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

  if (jvalue.HasMember("assets"))
  {
    const rapidjson::Value& jassets = jvalue["assets"];
    if (!CAssetsBuilder::instance.Do(rpAsset, jassets, NULL))
    {
      return false;
    }
  }

  const rapidjson::Value& jlayout = jvalue["layout"];
  if (!CLayout::builder.Do(rpAsset, jlayout, &rpPanel->layout))
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

  return true;
}

}
}

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
  return res;
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

  const rapidjson::Value& jwidgets = jvalue["widgets"];
  assert(jwidgets.IsArray());
  if (!jwidgets.IsArray()) return false;

  for (int i = 0; i < jwidgets.Size(); ++i)
  {
    const rapidjson::Value& jwidget = jwidgets[i];
    if (!jwidget.IsObject()) continue;
    const rapidjson::Value& jwidgettype = jwidget["type"];
    if (!jwidgettype.IsString()) continue;
    const IBuilder* builder_ptr = CBuilderManager::instance.Get(jwidgettype.GetString());
    if (NULL == builder_ptr) continue;
    if (builder_ptr->name == "panel")
    {
      // TODO: where to delete?
      IPanel* new_panel_ptr = new CPanel(rpPanel->scene, rpPanel);
      const TBuilder<IPanel* const>* panel_builder_ptr = reinterpret_cast<const TBuilder<IPanel* const>*>(builder_ptr);
      panel_builder_ptr->Do(rpAsset, jwidget, new_panel_ptr);
      rpPanel->Add(new_panel_ptr);
    }
    else if (builder_ptr->name == "image")
    {
      // TODO: where to delete?
      IImage* new_image_ptr = new CImage(rpPanel->scene, rpPanel);
      const TBuilder<IImage* const>* image_builder_ptr = reinterpret_cast<const TBuilder<IImage* const>*>(builder_ptr);
      image_builder_ptr->Do(rpAsset, jwidget, new_image_ptr);
      rpPanel->Add(new_image_ptr);
    }
    else if (builder_ptr->name == "file")
    {
      rapidjson::Document doc;
      const TBuilder<rapidjson::Document>* file_builder_ptr = reinterpret_cast<const TBuilder<rapidjson::Document>*>(builder_ptr);
      file_builder_ptr->Do(rpAsset, jwidget, doc);
      Do(rpAsset, doc, rpPanel);
    }
  }

  //TODO:
  return true;
}

}
}

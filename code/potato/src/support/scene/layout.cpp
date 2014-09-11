#include "layout.h"

namespace c4g {
namespace scene {

CLayout::CBuilder CLayout::builder;

CLayout::CLayout()
  : ILayout()
{
  ;
}

CLayout::~CLayout()
{
  ;
}

void CLayout::Resize(IWidget* const& rpWidget, const float& rfWidth, const float& rfHeight) const
{
  if (NULL == rpWidget) return;

  switch (type)
  {
  case ELayoutType_None:
    break;

  case ELayoutType_Scale:
    rpWidget->dst.l = C4G_GET_MID_RATIO(0, width, 0, rfWidth, rpWidget->dst_config.l);
    rpWidget->dst.r = C4G_GET_MID_RATIO(0, width, 0, rfWidth, rpWidget->dst_config.r);
    rpWidget->dst.t = C4G_GET_MID_RATIO(0, height, 0, rfHeight, rpWidget->dst_config.t);
    rpWidget->dst.b = C4G_GET_MID_RATIO(0, height, 0, rfHeight, rpWidget->dst_config.b);
    rpWidget->dst();
    break;

  case ELayoutType_FitIn:
    break;

  case ELayoutType_FitOut:
    break;
  }
  //TODO:

  rpWidget->Resize(rpWidget->dst.w, rpWidget->dst.h);
}

bool CLayout::CBuilder::Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, ILayout* const & rpLayout) const
{
  const rapidjson::Value& jtype = roConfig["type"];
  if (!jtype.IsString()) return false;
  const rapidjson::Value& jwidth = roConfig["w"];
  if (!jwidth.IsDouble()) return false;
  const rapidjson::Value& jheight = roConfig["h"];
  if (!jheight.IsDouble()) return false;

  rpLayout->type = Convert(jtype.GetString());
  rpLayout->width = static_cast<float>(jwidth.GetDouble());
  rpLayout->height = static_cast<float>(jheight.GetDouble());
  return true;
}

ELayoutType CLayout::CBuilder::Convert(const std::string& rsType) const
{
  if (rsType == "scale") return ELayoutType_Scale;
  else if (rsType == "fitin") return ELayoutType_FitIn;
  else if (rsType == "fitout") return ELayoutType_FitOut;
  return ELayoutType_None;
}

}
}

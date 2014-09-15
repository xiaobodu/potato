#include "layout.h"

#include "common.h"
#include "math.h"

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

void CLayout::Resize(const RectF& roConfig, const RectF& roResized, IWidget* const& rpWidget) const
{
  if (NULL == rpWidget) return;

  switch (type)
  {
  case ELayoutType_None:
    break;

  case ELayoutType_Scale:
    rpWidget->dst.l = C4G_GET_MID_RATIO(roConfig.l, roConfig.r, roResized.l, roResized.r, rpWidget->dst_config.l);
    rpWidget->dst.r = C4G_GET_MID_RATIO(roConfig.l, roConfig.r, roResized.l, roResized.r, rpWidget->dst_config.r);
    rpWidget->dst.t = C4G_GET_MID_RATIO(roConfig.t, roConfig.b, roResized.t, roResized.b, rpWidget->dst_config.t);
    rpWidget->dst.b = C4G_GET_MID_RATIO(roConfig.t, roConfig.b, roResized.t, roResized.b, rpWidget->dst_config.b);
    rpWidget->dst();
    break;

  case ELayoutType_FitIn:
    break;

  case ELayoutType_FitOut:
    break;
  }
  //TODO:

  if (rpWidget->resize) rpWidget->Resize(rpWidget->dst.w, rpWidget->dst.h);
}

bool CLayout::CBuilder::Do(ISceneImpl* const& rpScene, const rapidjson::Value& roConfig, ILayout* const & rpLayout) const
{
  const rapidjson::Value& jtype = roConfig["type"];
  if (!jtype.IsString()) return false;

  rpLayout->type = Convert(jtype.GetString());
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

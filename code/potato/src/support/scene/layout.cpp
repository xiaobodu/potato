#include "layout.h"

namespace c4g {
namespace scene {

CLayout::CLayout()
{
  ;
}

CLayout::~CLayout()
{
  ;
}

void CLayout::Resize(const int& riWidth, const int& riHeight)
{
  //TODO:
}

bool CLayout::CBuilder::Do(core::IAsset* const& rpAsset, const rapidjson::Value& roConfig, ILayout* const & rpLayout) const
{
  //
  return true;
}

CLayout::CBuilder CLayout::builder;

}
}

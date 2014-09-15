#include "widget.h"

namespace c4g {
namespace scene {

CEffectNone CEffectNone::instance;
CDealDelete CDealDelete::instance;

void CDealDelete::On(IWidget*& rpWidget) const
{
  delete rpWidget;
  rpWidget = NULL;
}


}
}

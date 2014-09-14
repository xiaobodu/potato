#include "widget.h"

namespace c4g {
namespace scene {


CDealDelete CDealDelete::instance;

void CDealDelete::On(IWidget*& rpWidget) const
{
  delete rpWidget;
  rpWidget = NULL;
}


}
}

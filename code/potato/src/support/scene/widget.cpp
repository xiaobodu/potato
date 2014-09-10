#include "widget.h"

namespace c4g {
namespace scene {


void CDealDelete::On(IWidget*& rpWidget) const
{
  delete rpWidget;
  rpWidget = NULL;
}

CDealDelete CDealDelete::instance;


}
}

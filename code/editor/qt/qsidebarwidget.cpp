#include "qsidebarwidget.h"

namespace c4g {
namespace qt {


QSideBarWidget::QSideBarWidget(QWidget* pParent /*= 0*/)
  : QWidget(pParent)
{
  m_oUi.setupUi(this);
}

QSideBarWidget::~QSideBarWidget()
{
  ;
}


}
}

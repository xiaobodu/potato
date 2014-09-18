#include "qpropertywidget.h"

namespace c4g {
namespace qt {

QPropertyWidget::QPropertyWidget(QWidget* pParent /*= 0*/)
  : QWidget(pParent)
{
  m_oUi.setupUi(this);
}

QPropertyWidget::~QPropertyWidget()
{
  ;
}

}
}

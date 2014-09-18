#pragma once

#include "qpropertywidget_ui.h"

#include <QtWidgets/QWidget>

namespace c4g {
namespace qt {

class QPropertyWidget : public QWidget
{
  Q_OBJECT

public:
  QPropertyWidget(QWidget* pParent = 0);
  virtual ~QPropertyWidget();

public:
  Ui::PropertyWidget m_oUi;
};


}
}

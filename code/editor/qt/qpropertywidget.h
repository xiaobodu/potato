#pragma once

#include "qpropertywidget_ui.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QTreeWidget>

namespace c4g {
namespace qt {

class QPropertyWidget : public QWidget
{
  Q_OBJECT

public:
  QPropertyWidget(QWidget* pParent = 0);
  virtual ~QPropertyWidget();

public Q_SLOTS:
  void UpdateWidget(QTreeWidgetItem* pItem, int iColum);
  void LostWidget();

private:
  Ui::PropertyWidget m_oUi;
};


}
}

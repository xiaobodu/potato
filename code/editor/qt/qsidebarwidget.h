#pragma once

#include "qsidebarwidget_ui.h"

#include <QtWidgets/QWidget>

namespace c4g {
namespace qt {

class QSideBarWidget : public QWidget
{
  Q_OBJECT

public:
  QSideBarWidget(QWidget* pParent = 0);
  virtual ~QSideBarWidget();

public:
  Ui::SideBarWidget m_oUi;
};


}
}

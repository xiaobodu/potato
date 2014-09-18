#pragma once

#include "scene_impl.h"

#include "qsidebarwidget_ui.h"

#include <QtWidgets/QWidget>

namespace c4g {
namespace qt {

class QSideBarWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QSideBarWidget(QWidget *parent = 0);
  ~QSideBarWidget();

public Q_SLOTS:
  void UpdateScene(c4g::scene::ISceneImpl*const pScene);

private:
  Ui::SideBarWidget m_oUi;
};

}
}

#include "qsidebarwidget.h"

#include "../editor_common.h"
#include "scene.h"

#include "qgleswidget.h"

namespace c4g {
namespace qt {

QSideBarWidget::QSideBarWidget(QWidget *parent)
  : QWidget(parent)
{
  m_oUi.setupUi(this);
}

QSideBarWidget::~QSideBarWidget()
{
  ;
}

void QSideBarWidget::UpdateScene(c4g::scene::ISceneImpl*const pScene)
{
  QString path = "";
  path = "aa";
}

}
}

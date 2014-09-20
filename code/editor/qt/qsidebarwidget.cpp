#include "qsidebarwidget.h"

#include "../editor_common.h"
#include "scene_impl.h"

#include "qgleswidget.h"
#include "qscenetreewidget.h"

namespace c4g {
namespace qt {

QSideBarWidget::QSideBarWidget(QWidget *parent)
  : QWidget(parent)
{
  m_oUi.setupUi(this);

  m_oUi.twScene->headerItem()->setText(0, "id");
  m_oUi.twScene->headerItem()->setText(1, "class");
}

QSideBarWidget::~QSideBarWidget()
{
  ;
}

void QSideBarWidget::UpdateScene(c4g::scene::ISceneImpl*const pScene)
{
  m_oUi.propertyWidget->LostWidget();
  m_oUi.twScene->UpdateScene(pScene);
}

}
}

#include "qscenetreewidget.h"

#include "../editor_common.h"
#include "scene_impl.h"
#include "panel.h"

#include <QtCore/QVariant>

namespace c4g {
namespace qt {

QSceneTreeWidget::QSceneTreeWidget(QWidget* pParent /*= 0*/)
  : QTreeWidget(pParent)
{
  headerItem()->setText(0, "id");
  headerItem()->setText(1, "class");
}

QSceneTreeWidget::~QSceneTreeWidget()
{
  ;
}

void QSceneTreeWidget::UpdateScene(c4g::scene::ISceneImpl* const& rpScene)
{
  clear();

  scene::IPanel* const& panel_ptr = rpScene->GetPanel();

  QTreeWidgetItem* item = new QTreeWidgetItem(this);
  item->setData(0, Qt::UserRole, qVariantFromValue((void*)panel_ptr));
  item->setText(0, panel_ptr->id.c_str());
  item->setToolTip(0, item->text(0));
  item->setText(1, panel_ptr->class_name.c_str());
  item->setToolTip(1, item->text(1));
  addTopLevelItem(item);

  m_vItemPtr.push_back(item);
  panel_ptr->Visit(this);
}

void QSceneTreeWidget::On(scene::IWidget* const& rpWidget)
{
  if (NULL == rpWidget || m_vItemPtr.empty()) return;

  QTreeWidgetItem* parent = m_vItemPtr[m_vItemPtr.size() - 1];
  if (NULL != parent)
  {
    QTreeWidgetItem* item = new QTreeWidgetItem(parent);
    item->setData(0, Qt::UserRole, qVariantFromValue((void*)rpWidget));
    item->setText(0, rpWidget->id.c_str());
    item->setToolTip(0, item->text(0));
    item->setText(1, rpWidget->class_name.c_str());
    item->setToolTip(1, item->text(1));
    parent->addChild(item);

    m_vItemPtr.push_back(item);
    rpWidget->Visit(this);
  }
  m_vItemPtr.pop_back();
}

}
}

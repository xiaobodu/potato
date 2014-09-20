#pragma once

#include "scene_base.h"

#include <vector>

#include <QtWidgets/QTreeWidget>

namespace c4g {
namespace scene {
class ISceneImpl;
}
namespace qt {

class QSceneTreeWidget : public QTreeWidget, public scene::IWidget::IVisitor
{
  Q_OBJECT

public:
  QSceneTreeWidget(QWidget* pParent = 0);
  virtual ~QSceneTreeWidget();

public:
  void UpdateScene(c4g::scene::ISceneImpl* const& rpScene);

protected:
  virtual void On(scene::IWidget* const& rpWidget);

private:
  std::vector<QTreeWidgetItem*> m_vItemPtr;
};

}
}

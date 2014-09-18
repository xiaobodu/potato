#pragma once

#include <QtWidgets/QTreeWidget>

namespace c4g {
namespace qt {

class QSceneTreeWidget : public QTreeWidget
{
  Q_OBJECT

public:
  QSceneTreeWidget(QWidget* pParent = 0);
  virtual ~QSceneTreeWidget();

public:
};

}
}

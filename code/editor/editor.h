#pragma once

#include "editor_common.h"
#include "editor_mainwindow_ui.h"

#include <QtWidgets/QMainWindow>

namespace c4g {
namespace core {
class IScene;
}

namespace potato {

class Editor : public QMainWindow
{
  Q_OBJECT

public:
  Editor(QWidget* pParent = NULL);
  virtual ~Editor();

Q_SIGNALS:
  void ToLoadScene(QString sScenePath);

public Q_SLOTS:
  void OnMenuBarPotatoNew();
  void OnMenuBarPotatoOpen();
  void OnMenuBarPotatoSave();
  void OnMenuBarHelpAbout();

private:
  Ui::MainWindow        m_oUi;
  QString               m_sScenePath;

public:
  static core::IScene* scene_ptr;
};

}
}

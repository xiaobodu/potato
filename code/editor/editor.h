#pragma once

#include "editor_mainwindow_ui.h"

#include <QtWidgets/QMainWindow>

namespace c4g {
namespace potato {

class Editor : public QMainWindow
{
  Q_OBJECT

public:
  Editor(QWidget* pParent = NULL);
  virtual ~Editor();

public Q_SLOTS:
  void OnMenuBarPotatoNew();
  void OnMenuBarPotatoOpen();
  void OnMenuBarPotatoSave();
  void OnMenuBarHelpAbout();

public:
  Ui::MainWindow         m_oUi;
};

}
}

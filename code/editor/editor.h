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

public:
  bool Initialize(const int& riSize, const char* const paArgv[]);

Q_SIGNALS:
  void ToLoadScene(QString sScenePath);

public Q_SLOTS:
  void OnMenuBarPotatoNew();
  void OnMenuBarPotatoOpen();
  void OnMenuBarPotatoSave();
  void OnMenuBarHelpAbout();

private:
  typedef std::map<std::string, std::string> TMapStr2Str;
  void ParseArgs(TMapStr2Str& rmArgs, const int& riSize, const char* const paArgv[], int iPos);

private:
  Ui::MainWindow        m_oUi;
  QString               m_sScenePath;
  core::MString2Module  m_mModule;

public:
  static core::IScene* scene_ptr;
};

}
}

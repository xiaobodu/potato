#include <QtWidgets/QFileDialog>
#include <QtWidgets/QApplication>

#include "editor.h"

#include "qt/qaboutdialog.h"


#if defined(MSVC)
#include <crtdbg.h>
#endif

namespace c4g {
namespace potato {

core::IScene* gs_pScene = NULL;

Editor::Editor(QWidget* pParent /*= NULL*/)
  : QMainWindow(pParent)
{
  m_oUi.setupUi(this);
}

Editor::~Editor()
{
  ;
}

void Editor::OnMenuBarPotatoNew()
{
  //TODO:
  ;
}

void Editor::OnMenuBarPotatoOpen()
{
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::Directory);
  dialog.setOption(QFileDialog::ShowDirsOnly);

  if (dialog.exec() == 0)
  {
      return;
  }
  m_sScenePath = dialog.directory().path();
  ToLoadScene(m_sScenePath);
}

void Editor::OnMenuBarPotatoSave()
{
  //TODO:
  ;
}

void Editor::OnMenuBarHelpAbout()
{
  QAboutDialog::ShowDialog(this);
}

}
}


int main(int argc, char* argv[])
{
#if defined(MSVC)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    QApplication a(argc, argv);
    c4g::potato::Editor editor;
    editor.show();
    return a.exec();
}

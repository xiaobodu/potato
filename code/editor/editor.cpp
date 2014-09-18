#include "editor.h"

#include "qt/qaboutdialog.h"

#include <QtWidgets/QApplication>

#if defined(MSVC)
#include <crtdbg.h>
#endif

namespace c4g {
namespace potato {

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
  //TODO:
  ;
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

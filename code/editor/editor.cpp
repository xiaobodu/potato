#include <QtWidgets/QFileDialog>
#include <QtWidgets/QApplication>

#include "editor.h"

#include "qt/qaboutdialog.h"

#include "utility/file.h"
#include "utility/sharedlibrary.h"

#if defined(MSVC)
#include <crtdbg.h>
#endif

namespace c4g {
namespace potato {

core::IScene* gs_pScene = NULL;
static utility::CSharedLibraryManager gs_SharedLibraryManager;

Editor::Editor(QWidget* pParent /*= NULL*/)
  : QMainWindow(pParent)
{
  //
}

Editor::~Editor()
{
  ;
}

bool Editor::Initialize(const int& riSize, const char* const paArgv[])
{
  TMapStr2Str args;
  ParseArgs(args, riSize - 1, paArgv + 1, 0);

  TMapStr2Str::const_iterator cit_module = args.find("module");
  if (cit_module == args.end())
  {
    printf("Usage: ** --module [PATH]\n");
    return false;
  }
  std::string module_path = cit_module->second;

  std::vector<std::string> file_list;
#if defined(CXX_MSVC)
  if (utility::GetListFiles(module_path, file_list, "*.dll") && !file_list.empty())
#else
  if (utility::GetListFiles(module_path, file_list) && !file_list.empty())
#endif
  {
    std::vector<std::string>::iterator it = file_list.begin();
    std::vector<std::string>::iterator it_end = file_list.end();
    for (; it != it_end; ++it)
    {
      core::IModule::CreateModuleFuncPtr create_func_ptr = gs_SharedLibraryManager.GetFunc<core::IModule::CreateModuleFuncPtr>(*it, TOSTRING(CreateModule));
      core::IModule::DestroyModuleFuncPtr destroy_func_ptr = gs_SharedLibraryManager.GetFunc<core::IModule::DestroyModuleFuncPtr>(*it, TOSTRING(DestroyModule));
      if (NULL == create_func_ptr || NULL == destroy_func_ptr) continue;
      core::IModule* module_ptr = NULL;
      create_func_ptr(module_ptr);
      if (NULL == module_ptr) continue;
      module_ptr->m_pCreateFunc = create_func_ptr;
      module_ptr->m_pDestroyFunc = destroy_func_ptr;
      m_mModule.insert(std::make_pair(module_ptr->type, module_ptr));
    }
  }

  m_oUi.setupUi(this);
  m_oUi.glesWidget->Initialize(m_mModule);
  return true;
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

void Editor::ParseArgs(TMapStr2Str& rmArgs, const int& riSize, const char* const paArgv[], int iPos)
{
  if (iPos >= riSize) return;
  if ('-' != paArgv[iPos][0] || '-' != paArgv[iPos][1]) return;

  std::string key;
  key.append(paArgv[iPos] + 2);
  ++iPos;

  std::string value;
  while (iPos < riSize)
  {
    if ('-' == paArgv[iPos][0] && '-' == paArgv[iPos][1]) break;
    if (!value.empty()) value.append(" ");
    value.append(paArgv[iPos]);
    ++iPos;
  }
  rmArgs.insert(std::make_pair(key, value));

  ParseArgs(rmArgs, riSize, paArgv, iPos);
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
    if (!editor.Initialize(argc, argv))
    {
      return 0;
    }
    editor.show();
    return a.exec();
}

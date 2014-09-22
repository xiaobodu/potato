/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef EDITOR_MAINWINDOW_UI_H
#define EDITOR_MAINWINDOW_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qgleswidget.h"
#include "qsidebarwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionTutorial;
    QAction *actionAbout;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionQuit;
    QAction *actionEffect;
    QAction *actionPlayInBar;
    QAction *actionEditInBar;
    QAction *actionSideBar;
    QAction *actionProject;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    c4g::qt::QGLESWidget *glesWidget;
    QMenuBar *menubar;
    QMenu *menuPotato;
    QMenu *menuHelp;
    QMenu *menuView;
    QStatusBar *statusbar;
    QDockWidget *dockSideBar;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_3;
    c4g::qt::QSideBarWidget *sidebarWidget;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(640, 480);
        MainWindow->setMinimumSize(QSize(0, 0));
        actionTutorial = new QAction(MainWindow);
        actionTutorial->setObjectName(QStringLiteral("actionTutorial"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionNew->setEnabled(false);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionOpen->setEnabled(true);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setEnabled(false);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionEffect = new QAction(MainWindow);
        actionEffect->setObjectName(QStringLiteral("actionEffect"));
        actionPlayInBar = new QAction(MainWindow);
        actionPlayInBar->setObjectName(QStringLiteral("actionPlayInBar"));
        actionEditInBar = new QAction(MainWindow);
        actionEditInBar->setObjectName(QStringLiteral("actionEditInBar"));
        actionEditInBar->setEnabled(false);
        actionSideBar = new QAction(MainWindow);
        actionSideBar->setObjectName(QStringLiteral("actionSideBar"));
        actionSideBar->setCheckable(true);
        actionSideBar->setChecked(true);
        actionProject = new QAction(MainWindow);
        actionProject->setObjectName(QStringLiteral("actionProject"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        glesWidget = new c4g::qt::QGLESWidget(centralwidget);
        glesWidget->setObjectName(QStringLiteral("glesWidget"));
        glesWidget->setMinimumSize(QSize(240, 240));

        verticalLayout->addWidget(glesWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 25));
        menuPotato = new QMenu(menubar);
        menuPotato->setObjectName(QStringLiteral("menuPotato"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockSideBar = new QDockWidget(MainWindow);
        dockSideBar->setObjectName(QStringLiteral("dockSideBar"));
        dockSideBar->setLayoutDirection(Qt::LeftToRight);
        dockSideBar->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        sidebarWidget = new c4g::qt::QSideBarWidget(dockWidgetContents);
        sidebarWidget->setObjectName(QStringLiteral("sidebarWidget"));

        verticalLayout_3->addWidget(sidebarWidget);

        dockSideBar->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockSideBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuPotato->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuPotato->addAction(actionNew);
        menuPotato->addSeparator();
        menuPotato->addAction(actionOpen);
        menuPotato->addAction(actionSave);
        menuPotato->addSeparator();
        menuPotato->addAction(actionQuit);
        menuHelp->addAction(actionAbout);
        menuView->addAction(actionSideBar);
        toolBar->addAction(actionEditInBar);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionSideBar, SIGNAL(toggled(bool)), dockSideBar, SLOT(setVisible(bool)));
        QObject::connect(dockSideBar, SIGNAL(visibilityChanged(bool)), actionSideBar, SLOT(setChecked(bool)));
        QObject::connect(actionAbout, SIGNAL(triggered()), MainWindow, SLOT(OnMenuBarHelpAbout()));
        QObject::connect(actionNew, SIGNAL(triggered()), MainWindow, SLOT(OnMenuBarPotatoNew()));
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(OnMenuBarPotatoOpen()));
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindow, SLOT(OnMenuBarPotatoSave()));
        QObject::connect(glesWidget, SIGNAL(DidLoadScene(c4g::scene::ISceneImpl*const)), sidebarWidget, SLOT(UpdateScene(c4g::scene::ISceneImpl*const)));
        QObject::connect(MainWindow, SIGNAL(ToLoadScene(QString)), glesWidget, SLOT(ToLoadScene(QString)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Potato Editor", 0));
        actionTutorial->setText(QApplication::translate("MainWindow", "Tutorial", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "&About", 0));
        actionNew->setText(QApplication::translate("MainWindow", "&New", 0));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "&Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "&Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionEffect->setText(QApplication::translate("MainWindow", "Effect", 0));
        actionPlayInBar->setText(QApplication::translate("MainWindow", "Play", 0));
        actionEditInBar->setText(QApplication::translate("MainWindow", "Edit", 0));
        actionSideBar->setText(QApplication::translate("MainWindow", "Side Bar", 0));
        actionProject->setText(QApplication::translate("MainWindow", "Project", 0));
        menuPotato->setTitle(QApplication::translate("MainWindow", "&Potato", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "&View", 0));
        dockSideBar->setWindowTitle(QApplication::translate("MainWindow", "Side Bar", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // EDITOR_MAINWINDOW_UI_H

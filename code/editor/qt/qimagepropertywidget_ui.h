/********************************************************************************
** Form generated from reading UI file 'imagepropertywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QIMAGEPROPERTYWIDGET_UI_H
#define QIMAGEPROPERTYWIDGET_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImagePropertyWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *ImagePropertyWidget)
    {
        if (ImagePropertyWidget->objectName().isEmpty())
            ImagePropertyWidget->setObjectName(QStringLiteral("ImagePropertyWidget"));
        ImagePropertyWidget->resize(97, 97);
        verticalLayout = new QVBoxLayout(ImagePropertyWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new QGraphicsView(ImagePropertyWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);


        retranslateUi(ImagePropertyWidget);

        QMetaObject::connectSlotsByName(ImagePropertyWidget);
    } // setupUi

    void retranslateUi(QWidget *ImagePropertyWidget)
    {
        ImagePropertyWidget->setWindowTitle(QApplication::translate("ImagePropertyWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class ImagePropertyWidget: public Ui_ImagePropertyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QIMAGEPROPERTYWIDGET_UI_H

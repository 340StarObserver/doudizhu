/********************************************************************************
** Form generated from reading UI file 'registwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTWINDOW_H
#define UI_REGISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistWindow
{
public:

    void setupUi(QWidget *RegistWindow)
    {
        if (RegistWindow->objectName().isEmpty())
            RegistWindow->setObjectName(QStringLiteral("RegistWindow"));
        RegistWindow->resize(400, 300);

        retranslateUi(RegistWindow);

        QMetaObject::connectSlotsByName(RegistWindow);
    } // setupUi

    void retranslateUi(QWidget *RegistWindow)
    {
        RegistWindow->setWindowTitle(QApplication::translate("RegistWindow", "RegistWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class RegistWindow: public Ui_RegistWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTWINDOW_H

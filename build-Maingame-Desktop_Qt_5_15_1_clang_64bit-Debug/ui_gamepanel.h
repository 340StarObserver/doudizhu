/********************************************************************************
** Form generated from reading UI file 'gamepanel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEPANEL_H
#define UI_GAMEPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GamePanel
{
public:

    void setupUi(QWidget *GamePanel)
    {
        if (GamePanel->objectName().isEmpty())
            GamePanel->setObjectName(QString::fromUtf8("GamePanel"));
        GamePanel->resize(1000, 650);

        retranslateUi(GamePanel);

        QMetaObject::connectSlotsByName(GamePanel);
    } // setupUi

    void retranslateUi(QWidget *GamePanel)
    {
        GamePanel->setWindowTitle(QCoreApplication::translate("GamePanel", "GamePanel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GamePanel: public Ui_GamePanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEPANEL_H

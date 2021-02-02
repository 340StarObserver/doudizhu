/********************************************************************************
** Form generated from reading UI file 'gameoverframe.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEOVERFRAME_H
#define UI_GAMEOVERFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>

QT_BEGIN_NAMESPACE

class Ui_GameOverFrame
{
public:

    void setupUi(QFrame *GameOverFrame)
    {
        if (GameOverFrame->objectName().isEmpty())
            GameOverFrame->setObjectName(QString::fromUtf8("GameOverFrame"));
        GameOverFrame->setFrameShadow(QFrame::Raised);
        GameOverFrame->resize(400, 300);
        GameOverFrame->setFrameShape(QFrame::StyledPanel);

        retranslateUi(GameOverFrame);

        QMetaObject::connectSlotsByName(GameOverFrame);
    } // setupUi

    void retranslateUi(QFrame *GameOverFrame)
    {
        GameOverFrame->setWindowTitle(QCoreApplication::translate("GameOverFrame", "Frame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameOverFrame: public Ui_GameOverFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVERFRAME_H

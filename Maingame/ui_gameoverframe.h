/********************************************************************************
** Form generated from reading UI file 'gameoverframe.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEOVERFRAME_H
#define UI_GAMEOVERFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_GameOverFrame
{
public:

    void setupUi(QFrame *GameOverFrame)
    {
        if (GameOverFrame->objectName().isEmpty())
            GameOverFrame->setObjectName(QStringLiteral("GameOverFrame"));
        GameOverFrame->setFrameShadow(QFrame::Raised);
        GameOverFrame->resize(400, 300);
        GameOverFrame->setFrameShape(QFrame::StyledPanel);

        retranslateUi(GameOverFrame);

        QMetaObject::connectSlotsByName(GameOverFrame);
    } // setupUi

    void retranslateUi(QFrame *GameOverFrame)
    {
        GameOverFrame->setWindowTitle(QApplication::translate("GameOverFrame", "Frame", 0));
    } // retranslateUi

};

namespace Ui {
    class GameOverFrame: public Ui_GameOverFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVERFRAME_H

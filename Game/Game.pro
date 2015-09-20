#-------------------------------------------------
#
# Project created by QtCreator 2015-08-31T16:24:06
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app


SOURCES += main.cpp\
        gamewindow.cpp \
    card.cpp \
    cardcombine.cpp \
    player.cpp \
    datapackage.cpp \
    gamework.cpp \
    gameserver.cpp \
    usermodel.cpp \
    loginbusiness.cpp

HEADERS  += gamewindow.h \
    point.h \
    huase.h \
    card.h \
    cardcombine.h \
    player.h \
    datapackage.h \
    datatype.h \
    gamework.h \
    gameserver.h \
    loginbusiness.h \
    usermodel.h

FORMS    += gamewindow.ui

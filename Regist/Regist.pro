#-------------------------------------------------
#
# Project created by QtCreator 2015-08-27T08:39:39
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Regist
TEMPLATE = app


SOURCES += main.cpp\
        registwindow.cpp \
    usermodel.cpp \
    registserver.cpp

HEADERS  += registwindow.h \
    usermodel.h \
    registserver.h

FORMS    += registwindow.ui

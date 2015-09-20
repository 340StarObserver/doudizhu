#-------------------------------------------------
#
# Project created by QtCreator 2015-09-01T21:17:26
#
#-------------------------------------------------

QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Maingame
TEMPLATE = app


SOURCES += main.cpp\
        maingame.cpp \
    gamesound.cpp \
    login.cpp \
    register.cpp \
    datapackage.cpp \
    clientsocket.cpp \
    player.cpp \
    chatwindow.cpp \
    infoitem.cpp \
    warregion.cpp \
    index.cpp \
    card.cpp \
    cardpicture.cpp \
    gameprocess.cpp \
    hand.cpp \
    method.cpp \
    robot.cpp \
    userplayer.cpp \
    wanjia.cpp \
    gameoverframe.cpp \
    cardlist.cpp \
    maininterface.cpp

HEADERS  += maingame.h \
    gamesound.h \
    login.h \
    register.h \
    datatype.h \
    datapackage.h \
    clientsocket.h \
    player.h \
    chatwindow.h \
    infoitem.h \
    warregion.h \
    index.h \
    card.h \
    cardpicture.h \
    gameprocess.h \
    hand.h \
    method.h \
    robot.h \
    userplayer.h \
    wanjia.h \
    gameoverframe.h \
    cardlist.h \
    maininterface.h

FORMS    += maingame.ui \
    login.ui \
    register.ui \
    chatwindow.ui \
    infoitem.ui \
    warregion.ui \
    index.ui \
    gamepanel.ui \
    gameoverframe.ui \
    cardlist.ui \
    maininterface.ui

RESOURCES += \
    res.qrc \
    img.qrc
RC_FILE += myico.rc

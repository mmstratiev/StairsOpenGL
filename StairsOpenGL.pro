#-------------------------------------------------
#
# Project created by QtCreator 2018-03-29T12:12:18
#
#-------------------------------------------------

QT       += core widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StairsOpenGL
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    openglwidget.cpp \
    stairs.cpp \
    inputmanager.cpp \
    platformstairs.cpp \
    ustairs.cpp \
    camera3d.cpp

HEADERS += \
        mainwindow.h \
    openglwidget.h \
    vertex.h \
    stairs.h \
    drawableglinterface.h \
    inputmanager.h \
    platformstairs.h \
    ustairs.h \
    camera3d.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc

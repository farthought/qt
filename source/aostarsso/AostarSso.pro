#-------------------------------------------------
#
# Project created by QtCreator 2015-06-11T15:22:12
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(qtsingleapplication/src/qtsingleapplication.pri)
TARGET = AostarSso
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    ahttp.cpp \
    adaemon.cpp \
    shadowwidget.cpp \
    staticbutton.cpp \
    common.cpp

HEADERS  += widget.h \
    ahttp.h \
    adaemon.h \
    common.h \
    shadowwidget.h \
    staticbutton.h

FORMS    += widget.ui

RESOURCES += \
    img.qrc

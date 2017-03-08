#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T12:38:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainWindow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintwidget.cpp \
    shape.cpp \
    line.cpp \
    rect.cpp

HEADERS  += mainwindow.h \
    paintwidget.h \
    shape.h \
    line.h \
    rect.h

RESOURCES += \
    source.qrc

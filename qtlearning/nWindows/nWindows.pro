#-------------------------------------------------
#
# Project created by QtCreator 2016-08-17T14:14:03
# 该程序用于测试多窗口切换
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nWindows
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindlg.cpp

HEADERS  += mainwindow.h \
    logindlg.h

FORMS    += mainwindow.ui \
    logindlg.ui

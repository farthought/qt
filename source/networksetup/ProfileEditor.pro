#-------------------------------------------------
#
# Project created by QtCreator 2015-07-02T14:43:40
# 网络配置修改，并且可以动态切换语言。
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ipcfg
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

TRANSLATIONS += ipcfg.ts
TRANSLATIONS += ipcfg_english.ts ipcfg_ko.ts

RESOURCES += \
    resource.qrc

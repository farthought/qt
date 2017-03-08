#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T16:16:33
# 该程序用于在系统中打开程序时，创建任务栏面板
# 具体的使用是为了配合启明星虚拟应用程序调用，创建面板
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = systemtray
TEMPLATE = app


SOURCES += ./src/main.cpp\
        ./src/widget.cpp\
         ./src/profileeditor.cpp

HEADERS  += ./src/widget.h\
              ./src/profileeditor.h

RESOURCES += \
    qtaction.qrc

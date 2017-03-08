#-------------------------------------------------
#
# Project created by QtCreator 2016-08-17T15:11:56
# 模拟登陆程序，用户名：gengshixin，密码：123456
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = login
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    logindialog.h

FORMS    += mainwindow.ui \
    logindialog.ui

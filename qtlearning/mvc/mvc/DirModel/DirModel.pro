#-------------------------------------------------
#
# Project created by QtCreator 2017-03-10T10:30:31
# 该程序使用QFileSystemModel和QTreeView对象显示文件夹内
# 容，并且可以创建和删除文件夹
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DirModel
TEMPLATE = app


SOURCES += main.cpp\
        dirmodel.cpp

HEADERS  += dirmodel.h

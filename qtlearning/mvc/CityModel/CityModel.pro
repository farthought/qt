#-------------------------------------------------
#
# Project created by QtCreator 2017-03-10T17:07:20
# 自定义model的方法，就是要覆盖我们所需要的那几个函数就可以了,rowCount
# columnCount,data,headerData等，本程序用于显示两个城市之间的距离
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CityModel
TEMPLATE = app


SOURCES += main.cpp\
        citymodel.cpp

HEADERS  += citymodel.h

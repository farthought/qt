#-------------------------------------------------
#
# Project created by QtCreator 2017-03-09T16:13:54
# item class类只是Qt为了方便我们使用而封装了的一些操作。比起真正的model-view类来，
# 那些类更易于使用，但是功能也会更简单，并且缺少实时性的支持，比如我们并不方便实现插入、
# 删除等一些常见操作。而本项目要说的model-view类使用起来可能会复杂一些，但是功能强大，
# 并且在model更新时会自动更新view，而model多是一些数据集合，因此比较便于操作。
# model-view类中，view大致有三种：list、tree和table，但是model千奇百怪，不同的业务，
# 甚至同样的业务不同的建模都会有不同的model。为了方便使用，Qt提供了一些预定义好的model
# 供我们使用。QStringListModel是其中最简单的一种。顾名思义，QStringListModel就是封
# 装了QStringList的model。QStringList是一种很常用的数据类型，它实际上是一个字符串列
# 表。我们可以想象，对于一个list来说，如果提供一个字符串列表形式的数据，就应该能够把这个
# 数据展示出来。因为二者是一致的：QStringList是线性的，而list也是线性的。所以，
# QStringListModel很多时候都会作为QListView的model。
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = listview
TEMPLATE = app


SOURCES += main.cpp\
        mylistview.cpp

HEADERS  += mylistview.h

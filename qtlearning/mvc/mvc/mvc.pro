#-------------------------------------------------
#
# Project created by QtCreator 2017-03-08T18:21:56
# 我们的系统有很多数据显示的需求，比如从数据库中把数据取出，
# 然后以自己的方式显示在我们自己的应用程序的界面中。进行这
# 一操作的典型方式是使用Qt的Item View类，这个程序主要是用
# 来演示Qt提供的一系列方便的item view类，包括 QListWidget,
# QTreeWidget, QTableWidget等，使用这些类可以直接对item
# 进行操作，我们可以使用这些类将数据方便的显示出来，当然遇到
# 复杂而庞大的数据就需要使用mvc架构来显示数据
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mvc
TEMPLATE = app


SOURCES += main.cpp\
        listwidget.cpp \
    treewidget.cpp \
    mainwindow.cpp \
    tablewidget.cpp

HEADERS  += listwidget.h \
    treewidget.h \
    mainwindow.h \
    tablewidget.h

RESOURCES += \
    icon.qrc

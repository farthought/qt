#-------------------------------------------------
#
# Project created by QtCreator 2017-03-10T12:23:47
# 本项目介绍QSortFilterProxyModel使用，该对象不能单独使用，
# 它只是一个“代理”，真正的数据需要另外的一个model提供，并且
# 它是用来排序和过滤的。所谓过滤，也就是说按照你输入的内容进行
# 数据的筛选，很像Excel里面的过滤器。不过Qt提供的过滤功能是基
# 于正则表达式的，因而功能强大。
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SortFilterProxy
TEMPLATE = app


SOURCES += main.cpp\
        sortfilterproxy.cpp

HEADERS  += sortfilterproxy.h

#-------------------------------------------------
#
# Project created by QtCreator 2017-03-10T14:41:39
# 自定义model,一个model中的每个数据元素都有一个model索引。这个索引指明
# 这个数据位于model的位置，比如行、列等。这就是QModelIndex。
# 每个数据元素还要有一组属性值，称为角色(roles)。这个属性值并不是数据的内容，
# 而是它的属性，比如说，这个数据是用来展示数据的，还是用于显示列头的？这组属
# 性值实际上是Qt的一个enum定义的，比较常见的有Qt::DisplayRole和Qt::EditRole，
# 另外还有Qt::ToolTipRole, Qt::StatusTipRole, 和Qt::WhatsThisRole等。
# 并且，还有一些属性是用来描述基本的展现属性的，比如Qt::FontRole,
# Qt::TextAlignmentRole, Qt::TextColorRole, Qt::BackgroundColorRole等
# 对于list model而言，要定位其中的一个数据只需要有一个行号就可以了，这个行号可以
# 通过QModelIndex::row()函数进行访问；对于table model而言，这种定位需要有两个
# 值：行号和列号，这两个值可以通过QModelIndex::row()和QModelIndex::column()
# 这两个函数访问到。另外，对于tree model而言，用于定位的可以是这个元素的父节点。
# 实际上，不仅仅是tree model，list model和table model的元素也都有自己的父节点，
# 只不过对于list model和table model，它们元素的父节点都是相同的，并且指向一个非法
# 的QModelIndex。对于所有的model，这个父节点都可以通过QModelIndex::parent()函
# 数访问到。这就是说，每个model的项都有自己的角色数据，0个、1个或多个子节点。既然每
# 个元素都有自己的子元素，那么它们就可以通过递归的算法进行遍历，就像数据结构中树的遍
# 历一样。
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurrencyModel
TEMPLATE = app


SOURCES += main.cpp\
        currencymodel.cpp

HEADERS  += currencymodel.h

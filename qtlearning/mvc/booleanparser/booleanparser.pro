#***********************************************************************************
# 这个例子是将布尔表达式分析成一棵树,这个分析过程在离散数学中经常遇到，特别是复杂的布尔表达式。类似
# 的分析方法可以套用于表达式化简、求值等一系列的运算。同时，这个技术也可以很方便地分析一个表达式是不
# 是一个正确的布尔表达式。在这个例子中，一共有四个类：
#   Node：组成树的节点；
#   BooleanModel：布尔表达式的模型，实际上这是一个树状模型，用于将布尔表达式形象地呈现为一棵树；
#   BooleanParser：分析布尔表达式的分析器；
#   BooleanWindow：图形用户界面，用户在此输入布尔表达式并进行分析，最后将结果展现成一棵树。
#***********************************************************************************


TEMPLATE      = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS       = booleanmodel.h \
                booleanparser.h \
                booleanwindow.h \
                node.h
SOURCES       = booleanmodel.cpp \
                booleanparser.cpp \
                booleanwindow.cpp \
                main.cpp \
                node.cpp

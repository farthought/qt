#ifndef BOOLEANWINDOW_H
#define BOOLEANWINDOW_H

#include <QWidget>

/***********************************************************************
 * BooleanModel类继承了QAbstractItemModel。之所以不继承QAbstractListModel
 * 或者QAbstractTableModel，是因为我们要构造一个带有层次结构的模型。在构造函数中，
 * 我们把根节点的指针赋值为 0，因此我们提供了另外的一个函数setRootNode()，将根节点
 * 进行有效地赋值。而在析构中，我们直接使用 delete 操作符将这个根节点释放掉。在
 * setRootNode()函数中，首先我们释放原有的根节点，再将根节点赋值。此时我们需要通知
 * 所有视图对界面进行重绘，以表现最新的数据：
 **********************************************************************/
class QLabel;
class QLineEdit;
class QTreeView;
class BooleanModel;

class BooleanWindow : public QWidget
{
    Q_OBJECT

public:
    BooleanWindow();

private slots:
    void booleanExpressionChanged(const QString &expr);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    BooleanModel *booleanModel;
    QTreeView *treeView;
};

#endif

#ifndef NODE_H
#define NODE_H

#include <QList>
#include <QString>

/***************************************************************************
 * Node很像一个典型的树的节点：一个Node指针类型的 parent 属性，保存父节点；一个QString
 * 类型的 str，保存数据。另外，Node还有一个Type属性，指明这个Node的类型，是一个词素，还
 * 是操作符，或者其他什么东西；children是QList<Node *>类型，保存这个 node 的所有子节点。
 * 注意，在 Node 类的析构函数中，使用了qDeleteAll()这个全局函数。这个函数是将 [start, end)
 * 范围内的所有元素进行 delete 运算。因此，它的参数的元素必须是指针类型的。并且，这个函数使
 * 用 delete 之后并不会将指针赋值为 0，所以，如果要在析构函数之外调用这个函数，建议在调
 * 用之后显示的调用clear()函数，将列表所有元素的指针重置为 0。
 **************************************************************************/
class Node
{
public:
    enum Type { Root, OrExpression, AndExpression, NotExpression, Atom,
                Identifier, Operator, Punctuator };

    Node(Type type, const QString &str = "");
    ~Node();

    Type type;
    QString str;
    Node *parent;
    QList<Node *> children;
};

#endif

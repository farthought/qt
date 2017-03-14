#ifndef BOOLEANPARSER_H
#define BOOLEANPARSER_H

#include "node.h"

/********************************************************************
 * BooleanParser作为核心类，并没有掺杂有关界面的任何代码。这是我们提出这个例子的
 * 另外一个重要原因：分层。对于初学者而言，如何设计好一个项目至关重要。分层就是其中
 * 一个重要的设计手法。或许你已经明白了 MVC 架构的基本概念，在这里也不再赘述。简单
 * 提一句，所谓分层，就是将程序的不同部分完全分离。比如这里的BooleanParser 类，
 * 仅仅是处理Node的节点，然后返回处理结果，至于处理结果如何显示，BooleanParser
 * 不去关心。通过前面我们了解到的 model/view 的相关知识也可以看出，这样做的好处
 * 是，今天我们可以使用QAbstractItemModel 来显示这个结果，明天我发现图形界面不
 * 大合适，我想换用字符界面显示——没问题，只需要替换掉用于显示的部分就可以了。
 *******************************************************************/
class BooleanParser
{
public:
    Node *parse(const QString &expr);

private:
    Node *parseOrExpression();
    Node *parseAndExpression();
    Node *parseNotExpression();
    Node *parseAtom();
    Node *parseIdentifier();
    void addChild(Node *parent, Node *child);
    void addToken(Node *parent, const QString &str, Node::Type type);
    bool matchToken(const QString &str) const;

    QString in;
    int pos;
};

#endif

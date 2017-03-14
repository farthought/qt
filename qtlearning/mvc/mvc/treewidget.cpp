#include "treewidget.h"
#include <QHBoxLayout>

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent)
{
    tree = new QTreeWidget(this);
    tree->setColumnCount(2);
    QStringList headers;
    headers << "Name" << "Number";
    tree->setHeaderLabels(headers);
    QStringList rootTextList;
    rootTextList << "Root" << "0";
    QTreeWidgetItem *root = new QTreeWidgetItem(tree, rootTextList);
    QStringList leafTextList;
    leafTextList << "leaf1" << "1";
    QTreeWidgetItem *leaf = new QTreeWidgetItem(root, leafTextList);
    root->addChild(leaf);
    QStringList leaf2TextList;
    leaf2TextList << "leaf2" << "2";
    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, leaf2TextList);
    leaf2->setCheckState(0, Qt::Checked);
    root->addChild(leaf2);
    QList<QTreeWidgetItem *> rootlist;
    rootlist << root;
    tree->insertTopLevelItems(0, rootlist);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tree);
    setLayout(layout);
}


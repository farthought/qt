#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>

class TreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = 0);

private:
    QTreeWidget *tree;

signals:

public slots:
};

#endif // TREEWIDGET_H

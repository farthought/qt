#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "listwidget.h"
#include "treewidget.h"
#include "tablewidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ListWidget *lsw;
    TreeWidget *tw;
    TableWidget *tbw;

signals:

public slots:
};

#endif // MAINWINDOW_H

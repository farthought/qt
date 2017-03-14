#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    lsw = new ListWidget(this);
    tw = new TreeWidget(this);
    tbw = new TableWidget(this);
    QLabel *label = new QLabel("this is a test");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lsw);
    layout->addWidget(tw);
    layout->addWidget(label);
    layout->addWidget(tbw);
    setLayout(layout);
}


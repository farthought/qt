#include "listwidget.h"
#include <QHBoxLayout>

ListWidget::ListWidget(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel;
    label->setFixedWidth(70);

    list = new QListWidget;
    list->addItem(new QListWidgetItem(QIcon(":/images/line.png"),tr("Line")));
    list->addItem(new QListWidgetItem(QIcon(":/images/oval.png"),tr("Oval")));
    list->addItem(new QListWidgetItem(QIcon(":/images/rect.png"),tr("Rect")));
    list->addItem(new QListWidgetItem(QIcon(":/images/triangle.png"),tr("Triangle")));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(list);
    list->setViewMode(QListView::IconMode);

    setLayout(layout);

    connect(list, SIGNAL(currentTextChanged(QString)), label, SLOT(setText(QString)));
}

ListWidget::~ListWidget()
{

}

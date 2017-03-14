#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent) : QWidget(parent)
{
    table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setRowCount(5);
    QStringList headers;
    headers <<"Line Number" << "ID" << "Name" << "Age" << "Sex";
    table->setHorizontalHeaderLabels(headers);
    table->setItem(0, 0, new QTableWidgetItem(QString("1")));
    table->setItem(1, 0, new QTableWidgetItem(QString("2")));
    table->setItem(2, 0, new QTableWidgetItem(QString("3")));
    table->setItem(3, 0, new QTableWidgetItem(QString("4")));
    table->setItem(4, 0, new QTableWidgetItem(QString("5")));
    table->setItem(0, 1, new QTableWidgetItem(tr("20100112")));
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(table);
    setLayout(layout);
}


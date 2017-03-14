#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>

class TableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = 0);
private:
    QTableWidget *table;

signals:

public slots:
};

#endif // TABLEWIDGET_H

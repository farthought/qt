#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QHBoxLayout>

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    ListWidget(QWidget *parent = 0);
    ~ListWidget();
private:
    QLabel *label;
    QListWidget *list;

};

#endif // LISTWIDGET_H

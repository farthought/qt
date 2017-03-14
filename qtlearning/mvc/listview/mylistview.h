#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H

#include <QWidget>
#include <QListView>
#include <QStringListModel>


class MyListView : public QWidget
{
    Q_OBJECT

public:
    MyListView(QWidget *parent = 0);
    ~MyListView();
private:
    QListView *listView;
    QStringListModel *listModel;

private slots:
    void insertData();
    void deleteData();
    void showData();
};

#endif // MYLISTVIEW_H

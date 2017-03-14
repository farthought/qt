#include "mylistview.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

MyListView::MyListView(QWidget *parent)
    : QWidget(parent)
{
    //创建model和stringlist，并将model的数据设置为stringlist
    listModel = new QStringListModel(this);
    QStringList data;
    data << "Letter A" << "Letter B" << "Letter C";
    listModel->setStringList(data);

    //创建qlistview对象，用于显示数据，并将该对象的model设置为listModel
    listView = new QListView(this);
    listView->setModel(listModel);

    //创建增，删，查按钮
    QHBoxLayout *btnlayout = new QHBoxLayout;
    QPushButton *insertBtn = new QPushButton("insert");
    QPushButton *deleteBtn = new QPushButton("delete");
    QPushButton *showBtn = new QPushButton("Show");
    btnlayout->addWidget(insertBtn);
    btnlayout->addWidget(deleteBtn);
    btnlayout->addWidget(showBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listView);
    mainLayout->addLayout(btnlayout);
    setLayout(mainLayout);

    //关联按钮信号
    connect(insertBtn, SIGNAL(clicked()), this, SLOT(insertData()));
    connect(deleteBtn, SIGNAL(clicked()), this, SLOT(deleteData()));
    connect(showBtn, SIGNAL(clicked()), this, SLOT(showData()));

}

MyListView::~MyListView()
{

}
/***********************************************
 *
 * Function:insertData
 * This function is used to insert data to the model
 *
 ***********************************************/
void MyListView::insertData()
{
    bool isOK;
    QString text = QInputDialog::getText(NULL, "Insert", "Please input new data:",
                                         QLineEdit::Normal, "You are inserting new data.", &isOK);
    if(isOK) {
        int row = listView->currentIndex().row();
        listModel->insertRows(row, 1);
        QModelIndex index = listModel->index(row);
        listModel->setData(index, text);
        listView->setCurrentIndex(index);
        listView->edit(index);
    }

}
/*********************************************
 *
 * this function is used to delete data from model,
 * but at least one data is remainded.
 *
 * *******************************************/
void MyListView::deleteData()
{
    if(listModel->rowCount() > 1) {
        listModel->removeRows(listView->currentIndex().row(), 1);
    }
}

void MyListView::showData()
{
    QStringList data = listModel->stringList();
    QString str;
    foreach(QString s, data) {
        str += s + "\n";
    }

    QMessageBox::information(this, "Data", str);
}

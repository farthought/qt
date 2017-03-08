#include "profileeditor.h"


ProfileEditor::ProfileEditor(QWidget *parent) :
    QWidget(parent)
{
    filename.clear();
    isSaved = 0;

    this->resize(600,400);
    label_fineName = new QLabel(tr("无配置文件"));
    tableView = new QTableView();
    button_Read = new QPushButton(tr("打开"));
    button_Save = new QPushButton(tr("保存")),
    button_Exit = new QPushButton(tr("退出"));
    button_help = new QPushButton(tr("帮助"));
    button_Addrow = new QPushButton(tr("新增"));

    model = new QStandardItemModel(tableView);
    QVBoxLayout *V1 = new QVBoxLayout();
    QHBoxLayout *H1 = new QHBoxLayout();
    QHBoxLayout *H2 = new QHBoxLayout();

    button_Read->setMinimumSize(10,5);
    button_Save->setMinimumSize(10,5);
    button_Exit->setMinimumSize(10,5);
    button_Addrow->setMinimumSize(10,5);
    button_help->setMinimumSize(10,5);

    H1->addWidget(button_Read);
    H1->addWidget(button_Save);
    H1->addWidget(button_Addrow);
    H1->addWidget(button_help);
    H1->addWidget(button_Exit);

    label_fineName->resize(600,20);
    H2->addWidget(label_fineName);
    H2->addLayout(H1);

    V1->addWidget(tableView);
    V1->addLayout(H2);

    connect (button_Read, SIGNAL(clicked()), this, SLOT(on_button_Read_clicked()));
    connect (button_Save, SIGNAL(clicked()), this, SLOT(on_button_Save_clicked()));
    connect (button_Exit, SIGNAL(clicked()), this, SLOT(on_button_Exit_clicked()));
    connect (button_help,SIGNAL(clicked()), this, SLOT(on_button_help_clicked()));
    connect (button_Addrow, SIGNAL(clicked()), this, SLOT(on_button_Addrow_clicked()));

    QIcon icon = QIcon("/usr/share/icons/appbox/set");
    this->setWindowIcon(icon);

    this->setLayout(V1);
    this->setWindowFlags(Qt::Window);
    this->setWindowTitle(tr("配置"));
    this->hide();
}

ProfileEditor::~ProfileEditor()
{
}


void ProfileEditor::model_init()
{
    //设置表头

    model->setColumnCount(2);

    model->setHeaderData(0,Qt::Horizontal,QString(tr("程序  ")));

    model->setHeaderData(1,Qt::Horizontal,QString(tr("启动命令")));

    tableView->setSortingEnabled(false);

    //model->setSortRole(Qt::DecorationRole);


    tableView->setModel(model);

    //表头信息显示居左
    tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);


    //设置列宽
    tableView->setColumnWidth(0,200);

    tableView->setColumnWidth(1,400);
}

void ProfileEditor::on_button_Read_clicked()
{
    //QString section("FPGA3");
    filename = QFileDialog::getOpenFileName(this,tr("打开配置文件"), "/etc/appbox", tr("(*.ini)"));
//    qDebug() << filename;
    if (0 == filename.length()) {
        int ret = QMessageBox::information(this, tr("温馨提示"), tr("您还没有选取任何配置文件"),tr("关闭"));
        if(ret == 0)
            label_fineName->setText(tr("无配置文件"));
        return ;
    } else {
        //QMessageBox::information(NULL, tr("Profile"), tr("You selected ") + filename);
        label_fineName->setText(filename);
    }
    profiledraw();
}

void ProfileEditor::on_button_Save_clicked()
{

    QString section("AppBox");
    QString Key;
    QStringList ValueList;
    int column = 1;

    filename = QFileDialog::getSaveFileName(this,tr("保存配置"), filename, tr("(*.ini)"));
    if (filename.isNull()) {
        return ;
    }

    QSettings *configIniSave = new QSettings(filename, QSettings::IniFormat);
    configIniSave->clear();
    configIniSave->beginGroup(section);

    for (int row =0 ;row < model->rowCount(); row++) {
        //qDebug()<<"-----"<<model->item(row, 0)->text();
        int sum = 0;
        Key.clear();
        ValueList.clear();
        if (model->item(row, 0) == NULL)
            continue;
        if (model->item(row,0)->text().isNull())
            continue;
        Key = model->item(row,0)->text().trimmed();
        for (column = 1; column < model->columnCount(); column++){
            if (model->item(row, column) == NULL || model->item(row, column)->text().isEmpty() || model->item(row, column)->text() == "\r\n")
                continue;
            else
            {
                sum++, ValueList.append("!" + model->item(row, column)->text().trimmed());
            }

        }
        if (sum == 0)
            continue;

        //qDebug()<<"save"<<Key<<ValueList;
        configIniSave->setValue(Key, ValueList);
    }
    configIniSave->endGroup();

    delete configIniSave;
    configIniSave = NULL;

    isSaved = 1;
    label_fineName->setText(filename);
}

void ProfileEditor::on_button_Exit_clicked()
{
    if (isSaved == 0) {
        int ret = QMessageBox::information(this,tr("提示"), tr("您确定不保存就退出吗?"),tr("保存"), tr("确定"));
        switch (ret) {
            case 0:
                on_button_Save_clicked();
                break;
            case 1:
                this->close();
                break;
            default:
                break;
        }
    } else {
        this->close();
    }
}

void ProfileEditor::on_button_help_clicked()
{
   int ret = QMessageBox::information(this, tr("使用帮助"),
                            tr("本文档是介绍如何修改配置文件的，默认的配置文件存储在/etc/appbox目录中，以app.ini命名"\
                               "\n具体的配置如下：\n1.首先点击打开按钮，并到/etc/appbox/目录下找到配置文件并打开；"\
                               "\n2.如果需要增加新的程序，只需点击新增，并按要求写入程序名和启动程序命令，点击保存，保存位置不变;\n3.如果需要"\
                               "删除程序，只需要将相应的程序名和程序命令清空，点击保存。\n4.如果要退出配置，点击退出或者关闭按钮。"),
                            tr("关闭"));
   if (ret == 0)
       return;
}

void ProfileEditor::on_button_Addrow_clicked()
{
    if (model->columnCount()==0)
        model_init();
    model->insertRow(model->rowCount());
    //qDebug()<<model->rowCount();
}

void ProfileEditor::parse(QString filename, KEYLIST *keys)
{

    QString curLine;
    QString section;

    struct _key tmpKey;

    int sum = 0;
    QFile *ini = new QFile(filename);
    if (!ini->open(QFile::ReadOnly)){
       // qDebug()<<"Open file error!";
        return;
    }

    while(!ini->atEnd()){
        curLine = QString (ini->readLine());
       // qDebug()<<"Current Line :"<<curLine;

        //section,such as "[FPGA3]"
        if (curLine.contains('[') && curLine.contains(']')){
            section = curLine.right(curLine.size() - curLine.indexOf('[') - 1) ;
            section = section.left(section.lastIndexOf(']'));
          //  qDebug()<<"get section"<<section;
            continue;
        }

        //Key,values
        if (curLine.contains('=')) {

            tmpKey.section = section;
            tmpKey.valuelist.clear();

            tmpKey.key = curLine.split('=').first();
            if (tmpKey.key.isEmpty())
                continue;

            //有键没有值，继续下次循环
            if (curLine.size() - tmpKey.key.size() - 1 <=0)
                continue;

//            qDebug() << curLine.size() << tmpKey.key.size();
            //',' 逗号作为分隔符
            QStringList tmp = curLine.right(curLine.size() - tmpKey.key.size() - 1).split(',');
            //值为空，或者换行，继续下次循环
            if (tmp.isEmpty() || tmp.first() == "\r\n" ||tmp.first() == "\n") {
                continue;
            }
            if (!curLine.right(curLine.size() - tmpKey.key.size() - 1).contains('!'))
                continue;
            tmpKey.valuelist = curLine.right(curLine.size() - tmpKey.key.size() - 1).trimmed().split('!')[1];
           // qDebug() << tmpKey.valuelist;
            }

            keys->append(tmpKey);
           // qDebug()<<(*keys)[sum].section<<(*keys)[sum].key<<(*keys)[sum].valuelist;
            sum++;
        }
    ini->close();

    return;
}

void ProfileEditor::closeEvent(QCloseEvent *e)
{
    e->ignore();
    widgetClose();
}

void ProfileEditor::widgetClose()
{
    this->destroy();
}

void ProfileEditor::profiledraw()
{
    model->clear();
    model_init();
    isSaved = 0;

    KEYLIST keys;
    int x = 0;
    int y = 0;
    parse(filename, &keys);
    //qDebug() << filename;
    for (x = 0; x != keys.size(); x++) {
        y = 0;
        model->setItem(x, y, new QStandardItem(keys[x].key));
       // qDebug()<<"y:"<<y<<"->"<<keys[x].key;
        y++;
        model->setItem(x, y, new QStandardItem(keys[x].valuelist));
        //qDebug()<<"y:"<<y<<"->"<<keys[x].valuelist;
        }
 }


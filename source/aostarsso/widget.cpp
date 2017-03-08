#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ahttp.h"
#include "common.h"
#include "staticbutton.h"

Widget::Widget(QWidget *parent) :
    ShadowWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags());
    m_http = new AHttp(this);
    this->setObjectName ("login");
    this->setStyleSheet ("#login{background-image: url(:/background);}");
//    this->resize        (442, 338);
    this->resize        (463, 335);
    this->setWindowTitle("统一办公登录平台");

    ui->warninglabel->hide();
    m_miniButton    = new StaticButton  (":/mini", true);
    m_closeButton   = new StaticButton  (":/close", true);
    m_loginButton   = new StaticButton  (":/login", true, 4, this);
    m_loginButton->move(90, 220);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch ();
    hLayout->addWidget  (m_miniButton,    0, Qt::AlignRight|Qt::AlignTop);
    hLayout->addWidget  (m_closeButton,   0, Qt::AlignRight|Qt::AlignTop);
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout          (hLayout);
    vLayout->addStretch         ();
    vLayout->setContentsMargins (0, 16, 16, 0);
    this->setLayout             (vLayout);
    this->initConnects          ();
    this->showWarning           ();

}

void Widget::showWarning()
{
    ui->warninglabel->show();
    ui->warninglabel->setStyleSheet("color:red");
    ui->warninglabel->setText("请您输入PMIS系统的用户名和密码!");


 }

QString Widget::getTGT() const
{
    return m_http->getTGT();
}

QString Widget::getUsername() const
{
    return ui->userEdit->text();
}

Widget::~Widget()
{
    delete ui;
}

//void Widget::changeEvent(QEvent *e)
//{
//    QWidget::changeEvent(e);
//    switch (e->type()) {
//    case QEvent::LanguageChange:
//        ui->retranslateUi(this);
//        break;
//    default:
//        break;
//    }
//}

void Widget::closeEvent(QCloseEvent *)
{
    qDebug()<< "closessss";
    emit closeSignal();
}


void Widget::initConnects()
{
    connect(m_loginButton,  SIGNAL(buttonClicked()),        this, SLOT(loginServer()));
    connect(ui->passwdEdit, SIGNAL(returnPressed()),        this, SLOT(loginServer()));
    connect(m_miniButton,   SIGNAL(buttonClicked()),        this, SLOT(showMini()));
    connect(m_closeButton,  SIGNAL(buttonClicked()),        this, SLOT(close()));
    connect(m_http,         SIGNAL(finishedSignal(bool)),   this, SLOT(loginFinished(bool)));
}

void Widget::loginServer()
{
    if(ui->userEdit->text().isEmpty() || ui->passwdEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "警告", "请输入用户名或密码", "确定");
    }else{
        m_loginButton->setEnabled(false);
        m_http->loginBaseServer(ui->userEdit->text(), ui->passwdEdit->text());
    //    emit loginFinishedSignal(true); // 测试

    }
}

void Widget::loginFinished(bool success)
{
    m_loginButton->setEnabled(true);
    if(success)
    {
        QMap<QString,QString> userinfo;
        userinfo.insert("username", ui->userEdit->text());
        userinfo.insert("passwd", QString(ui->passwdEdit->text().toUtf8().toBase64()));
        userinfo.insert("datetime" , QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
        userinfo.insert("lock", "1");
        QString iniPath = QDir::homePath() + USER_INI;
        QFileInfo fileinfo(iniPath);
        if(!fileinfo.absoluteDir().exists())
        {
            fileinfo.absoluteDir().mkpath(fileinfo.absolutePath());
        }
        myHelper::writeGroupConfig(iniPath, "userinfo", userinfo);
        myHelper::set_username(this->getUsername());
    //    qDebug()<<"aaaaa::"<<myHelper::get_username();
   //     qDebug()<<"this usrname::"<<this->getUsername();
//        QProcess *poc=new QProcess();
        QString string=QString("sudo bash /usr/bin/mount_volume.sh %1 &").arg(this->getUsername());
//        poc->start(string);
        QProcess::startDetached(string);

        ui->userEdit->clear();
        ui->passwdEdit->clear();

        this->close();


    }else
    {
        QMessageBox::warning(this, "错误", "用户名或密码错误", QMessageBox::Ok);
    }
    emit loginFinishedSignal(success);

}
void Widget::showMini()
{
    qDebug() << "showMini";
//    this->setWindowState(Qt::WindowMinimized);
    this->showMinimized();
}

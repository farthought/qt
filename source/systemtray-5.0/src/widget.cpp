#include "widget.h"
#include <QDebug>
Widget::Widget(QString iPath, QString aName, QString aCmd1, QString aCmd2, QString aCmd3, QWidget *parent)
    : QMainWindow(parent),iconPath(iPath),appName(aName), appCmd1(aCmd1), appCmd2(aCmd2), appCmd3(aCmd3)
{
    appCmd = appCmd1 + " " + appCmd2 + " " + appCmd3;
    qDebug() << "*****" << iconPath << appName << appCmd1 << appCmd2 << appCmd3 << appCmd;
    QIcon icon = QIcon(iPath);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip(appName);
    trayIcon->show();

    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this,SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
//    qDebug() << "*********"  << resault;
    trayIconMenu = new QMenu(this);
    open = new QAction(QIcon(":/actionicon/actionicon/open.png"),tr("打开"),this);
    connect(open, SIGNAL(triggered()), this, SLOT(openApp()));
    quit = new QAction(QIcon(":/actionicon/actionicon/exit.png"),tr("退出"), this);
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));


    trayIconMenu->addAction(open);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit);
    trayIcon->setContextMenu(trayIconMenu);
}

Widget::~Widget()
{

}

void Widget::trayiconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
         this->hide();
         QProcess::startDetached(appCmd);
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标
        this->hide();

        //this->raise();
        break;
    default:
        break;
    }
}


void Widget::openApp()
{
    qDebug() << "clicked.";
    QProcess::startDetached(appCmd);
}


#include "widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
{
    QString filename = "/etc/appbox/app.ini";
    QIcon icon = QIcon("/usr/share/icons/appbox/abiword");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip(tr("程序盒"));
    //QString titlec=tr("程序");
    //QString textc=tr("程序");
    trayIcon->show();
    //trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this,SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
    profeditor = new ProfileEditor(this);
//    appIni = new QSettings ("/home/sg-os/code/qt/test/app.ini", QSettings::IniFormat);
//    appIni->beginGroup("app");
//    QString resault = appIni->value("app1").toString();
//    appIni->endGroup();

//    qDebug() << "*********"  << resault;
    trayIconMenu = new QMenu(this);
    profeditor->parse(filename, &key_w);
    QListIterator<struct _key> iter(key_w);
    for(; iter.hasNext();)
    {
        struct _key test = iter.next();
       // qDebug() <<"+++++" << test.section << test.key << test.valuelist;
        QAction *app = new QAction(test.key, this);
        actionList.append(app);
        connect(app, SIGNAL(triggered()), this, SLOT(startl()));
        trayIconMenu->addAction(app);
    }
    set = new QAction(tr("配置"), this);
    connect(set, SIGNAL(triggered()), this, SLOT(showProfileEditor()));
    quit = new QAction(tr("退出"), this);
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));


    trayIconMenu->addAction(set);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit);
    trayIcon->setContextMenu(trayIconMenu);
}

Widget::~Widget()
{
    delete trayIcon;
    delete trayIconMenu;
    delete profeditor;
}

void Widget::trayiconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
         this->hide();
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标
        this->hide();
        //this->raise();
        break;
    default:
        break;
    }
}

void Widget::startl()
{
    QString command;
    QAction *appcom;
    int i = 0;
    QAction *app = qobject_cast <QAction*>(sender());
    if(!app)
        return;
    QListIterator<QAction*> iter(actionList);
    for(; iter.hasNext();)
    {
        appcom = iter.next();
        if(app == appcom)
        {
            command = key_w[i].valuelist;
         //   qDebug() << "====" << command;
            QProcess::startDetached(command,QStringList());
            return;
        }
        i++;
    }
}

void Widget::showProfileEditor()
{
  // qDebug() << "this is a test";
   profeditor = new ProfileEditor(this);
   profeditor->show();
}


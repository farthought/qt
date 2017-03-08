#include "adaemon.h"
#include <QSettings>
#include <QDir>
#include <QTimer>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QFile>
#include <QLabel>
#include <QTime>

#include "ahttp.h"
#include "common.h"
#include "widget.h"
#include "staticbutton.h"

ADaemon::ADaemon(QObject *parent) :
    QObject(parent)
{
    m_http      = new AHttp (this);
    m_timer     = new QTimer(this);
    m_timer->setInterval    (1200000);
    m_infoTimer = new QTimer(this);
    m_infoTimer->setInterval(5000);
    m_infoTimer->setSingleShot(true);
    this->initUI        ();
    this->initConnects  ();

    this->popLockWidget ();
}

void ADaemon::startDaemon()
{
    QString iniPath = QDir::homePath() + USER_INI;
    if(!QFile::exists(iniPath))
    {
        m_lockAction->setEnabled(false);
        m_unlockAction->setEnabled(false);
        //m_widget->showWarning();
        m_widget->show();
    }else{
        if(isLock())
        {
            m_lockAction->setEnabled(false);
            m_unlockAction->setEnabled(true);
            getTicket();
        }else{
            m_lockAction->setEnabled(true);
            m_unlockAction->setEnabled(false);
            m_widget->show();
        }
    }
}

void ADaemon::finished(bool success)
{
    if(success)
    {
        QTime   curTime = QTime::currentTime();
        int hour = curTime.hour();
        QString regards;
        if (hour >= 0 && hour < 6)
        {
            regards = "凌晨好";
        }
        else if (hour >= 6 && hour < 12)
        {
            regards = "早上好";
        }
        else if (hour >= 12 && hour < 18)
        {
            regards = "下午好";
        }
        else
        {
            regards = "晚上好";
        }

        m_lockAction->setEnabled(false);
        m_unlockAction->setEnabled(true);
        m_tray->setIcon(QIcon(":/tray_lock"));

        m_infoLabel->setText(QString("    %1 %2，您现在可以正常使用业务系统了！").arg(m_widget->getUsername().trimmed()).arg(regards));
        QFont font ("System", 10);
        m_infoLabel->setFont(font);

//        if(getDateTime().isEmpty())
//        {
//            m_datetimeLabel->setText("第一次登录");
//        }else
//        {
//            m_datetimeLabel->setText(QString("上次登录时间：%1").arg(getDateTime()));
//        }
        m_infoWidget->show();
        m_infoTimer->start();
        m_tgt = m_widget->getTGT();
        //m_timer->start();
    }else
    {
        m_lockAction->setEnabled(true);
        m_unlockAction->setEnabled(false);
        m_tray->setIcon(QIcon(":/tray_unlock"));
    }
}

void ADaemon::httpFinished(bool success)
{
    if(!success)
    {
        QMessageBox::warning(NULL, "警告", "统一认证失败", QMessageBox::Ok);
        m_tray->setIcon(QIcon(":/tray_unlock"));
        //m_timer->stop();
        QMap<QString, QString> userinfo;
        userinfo.insert("lock", "0");
        QString iniPath = QDir::homePath() + USER_INI;
        myHelper::writeGroupConfig(iniPath, "userinfo", userinfo);
        m_lockAction->setEnabled(true);
        m_unlockAction->setEnabled(false);
        QString stfile = "/tmp/ovd/pmis_parameter.ini";
        QFile::remove(stfile);
    }else{
        m_tray->setIcon(QIcon(":/tray_lock"));
        m_tgt = m_http->getTGT();
        //m_timer->start();
    }
}

void ADaemon::updateTicket()
{
    if(!m_tgt.isEmpty())
    {
        m_http->updateTicket(m_tgt);
    }
}

void ADaemon::lockUser()
{
    m_lockAction->setEnabled(false);
    m_unlockAction->setEnabled(false);
    m_widget->show();
    m_widget->showNormal();
    m_widget->activateWindow();
}

void ADaemon::unLockUser()
{
    if(QMessageBox::warning(NULL, tr("警告"), tr("您确定要解除账号绑定么？"),
                            QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
    {
        m_http->logout();
        //m_timer->stop();
        QMap<QString, QString> userinfo;
        userinfo.insert("lock", "0");
        QString iniPath = QDir::homePath() + USER_INI;
        myHelper::writeGroupConfig(iniPath, "userinfo", userinfo);
        m_lockAction->setEnabled(true);
        m_unlockAction->setEnabled(false);
        QString stfile = "/tmp/ovd/pmis_parameter.ini";
        QFile::remove(stfile);
        m_tray->setIcon(QIcon(":/tray_unlock"));
    }
}

void ADaemon::closeLockWidget()
{
    qDebug() << __PRETTY_FUNCTION__;
    if (isLock())
    {
        m_lockAction->setEnabled(false);
        m_unlockAction->setEnabled(true);
    }else
    {
        m_lockAction->setEnabled(true);
        m_unlockAction->setEnabled(false);
    }
}

void ADaemon::trayactivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick && !isLock())
    {
        m_widget->show();
        m_widget->showNormal();
        m_widget->activateWindow();
    }else if(reason == QSystemTrayIcon::Context && !m_widget->isActiveWindow() && !isLock())
    {
        m_lockAction->setEnabled(true);
        m_unlockAction->setEnabled(false);
    }
}


void ADaemon::initUI()
{
    m_widget = new Widget;
    myHelper::FormInCenter(m_widget);
    m_tray = new QSystemTrayIcon(this);
    m_tray->setIcon(QIcon(":/tray_unlock"));
    m_tray->setToolTip(tr("统一办公登录平台"));
    QMenu  *menu = new QMenu;
    m_lockAction = new QAction(QIcon(":/lock"),"账号绑定", menu);
    m_unlockAction  = new QAction(QIcon(":/unlock") , "解绑定", menu);
    menu->addAction(m_lockAction);
    menu->addAction(m_unlockAction);
    m_tray->setContextMenu(menu);
    m_tray->show();


    m_infoWidget = new ShadowWidget;
    m_infoWidget->setObjectName("info");
    m_infoWidget->setStyleSheet("#info{border-image:url(:/login_result);}");
    m_infoWidget->setFixedSize(QPixmap(":/login_result").size());
    //m_infoWidget->hide();
    myHelper::bottomRightWidget(m_infoWidget);
    m_closeButton = new StaticButton(":/close", true, 3, m_infoWidget);
    m_closeButton->move(m_infoWidget->width() - m_closeButton->width() - 2, 0);

    m_infoLabel = new QLabel(m_infoWidget);
    m_infoLabel->move(26, 60);
    m_infoLabel->setFixedWidth(200);
    m_infoLabel->setWordWrap(true);
    QFont font = m_infoLabel->font();
    font.setPointSize(12);
    m_infoLabel->setFont(font);

//    m_datetimeLabel = new QLabel(m_infoWidget);
//    m_datetimeLabel->move(20, 138);
//    m_datetimeLabel->setStyleSheet("color:gray;");
//    QFont datefont = m_datetimeLabel->font();
//    datefont.setPointSize(10);
//    m_datetimeLabel->setFont(datefont);
}

void ADaemon::initConnects()
{
    connect(m_timer,        SIGNAL(timeout()),                  this,           SLOT(updateTicket       ()));
    connect(m_widget,       SIGNAL(loginFinishedSignal(bool)),  this,           SLOT(finished           (bool)));
    connect(m_widget,       SIGNAL(closeSignal()),              this,           SLOT(closeLockWidget    ()));
    connect(m_http,         SIGNAL(finishedSignal(bool)),       this,           SLOT(httpFinished       (bool)));
    connect(m_lockAction,   SIGNAL(triggered()),                this,           SLOT(lockUser           ()));
    connect(m_unlockAction, SIGNAL(triggered()),                this,           SLOT(unLockUser         ()));
    connect(m_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayactivated(QSystemTrayIcon::ActivationReason)));
    connect(m_closeButton,  SIGNAL(buttonClicked()),            m_infoWidget,   SLOT(close              ()));
    connect(m_infoTimer,    SIGNAL(timeout()),                  m_infoWidget,   SLOT(close              ()));

}

bool ADaemon::isLock()
{
    QString iniPath = QDir::homePath() + USER_INI;
    if (!QFile::exists(iniPath))
    {
        return false;
    }
    else
    {
        QMap<QString,QString> userinfo;
        userinfo = myHelper::readGroupConfig (iniPath, "userinfo");
        if (userinfo.value("lock") == "1")
            return true;
        else
            return false;
    }
}

void ADaemon::getTicket()
{
    QString iniPath = QDir::homePath() + USER_INI;
    QMap<QString,QString> userinfo;
    userinfo = myHelper::readGroupConfig(iniPath, "userinfo");
    if(!userinfo.value("username").isEmpty() && !userinfo.value("passwd").isEmpty())
    {
        myHelper::set_username(userinfo.value("username"));

        m_http->loginServer(userinfo.value("username"), userinfo.value("passwd"));
    }
}

QString ADaemon::getDateTime() const
{
    QString iniPath = QDir::homePath() + USER_INI;
    QMap<QString,QString> userinfo;
    userinfo = myHelper::readGroupConfig(iniPath, "userinfo");
    return userinfo.value("datetime");
}

/// 重启后若已经绑定，弹框提示
void ADaemon::popLockWidget()
{
    if (false == this->isLock())
    {
        return ;
    }

    QString iniPath = QDir::homePath() + USER_INI;
    QMap<QString,QString> userinfo;
    userinfo = myHelper::readGroupConfig (iniPath, "userinfo");
    QString userName (userinfo.value("username"));

    QTime   curTime = QTime::currentTime();
    int hour = curTime.hour();
    QString regards;
    if (hour >= 0 && hour < 6)
    {
        regards = "凌晨好";
    }
    else if (hour >= 6 && hour < 12)
    {
        regards = "早上好";
    }
    else if (hour >= 12 && hour < 18)
    {
        regards = "下午好";
    }
    else
    {
        regards = "晚上好";
    }

    m_lockAction->setEnabled(false);
    m_unlockAction->setEnabled(true);
    m_tray->setIcon(QIcon(":/tray_lock"));
    m_infoLabel->setText(QString("    %1 %2，您现在可以正常使用业务系统了！").arg(userName).arg(regards));
    QFont font ("System", 10);
    m_infoLabel->setFont(font);


    m_infoWidget->show();
    m_infoTimer->start();
}

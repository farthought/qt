#ifndef ADAEMON_H
#define ADAEMON_H

#include <QObject>
#include <QMap>
#include <QSystemTrayIcon>
class AHttp;
class QTimer;
class Widget;
class QSystemTrayIcon;
class QAction;
class ShadowWidget;
class StaticButton;
class QLabel;

class ADaemon : public QObject
{
    Q_OBJECT
public:
    explicit ADaemon(QObject *parent = 0);
    void startDaemon();
signals:

public slots:
private slots:
    void finished(bool success);
    void httpFinished(bool success);
    void updateTicket();
    void lockUser();
    void unLockUser();
    void closeLockWidget();
    void trayactivated(QSystemTrayIcon::ActivationReason reason);
private:
    void initUI();
    void initConnects();
    bool isLock();
    void getTicket();
    QString getDateTime() const;
    void popLockWidget ();
private:
    AHttp *m_http;
    QTimer  *m_timer;
    QTimer  *m_infoTimer;
    Widget  *m_widget;
    QSystemTrayIcon *m_tray;
    QAction *m_lockAction;
    QAction *m_unlockAction;
    QString m_tgt;
    ShadowWidget    *m_infoWidget;
    StaticButton    *m_closeButton;
    QLabel          *m_infoLabel;
    QLabel          *m_datetimeLabel;
};

#endif // ADAEMON_H

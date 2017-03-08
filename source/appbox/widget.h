#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QProcess>
#include <QString>
#include <QSettings>
#include "profileeditor.h"

class Widget : public QMainWindow
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();
private slots:
       void trayiconActivated(QSystemTrayIcon::ActivationReason reason);
       void startl();
       void showProfileEditor();

private:
      QSystemTrayIcon *trayIcon;
      QAction *set;
      QAction *quit;
      QMenu   *trayIconMenu;
      QSettings *appIni;
      ProfileEditor *profeditor;
      KEYLIST key_w;
      QList <QAction*> actionList;

};

#endif // WIDGET_H

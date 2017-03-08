#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QProcess>
#include <QString>
#include <QSettings>
#include <QSystemTrayIcon>

class Widget : public QMainWindow
{
    Q_OBJECT
public:
    Widget(QString iPath="", QString aName = "", QString aCmd1 = "", QString aCmd2 = "", QString aCmd3 = "", QWidget *parent = 0);
    ~Widget();
private slots:
       void trayiconActivated(QSystemTrayIcon::ActivationReason reason);
       void openApp();

private:
      QString iconPath;
      QString appName;
      QString appCmd;
      QString appCmd1;
      QString appCmd2;
      QString appCmd3;
      QSystemTrayIcon *trayIcon;
      QAction *open;
      QAction *quit;
      QMenu   *trayIconMenu;

};

#endif // WIDGET_H

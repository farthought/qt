#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "shadowwidget.h"
class AHttp;
class StaticButton;
class QLineEdit;
class QLabel;
namespace Ui {
class Widget;
}

class Widget : public ShadowWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void showWarning();

    QString getTGT() const;
    QString getUsername() const;
    ~Widget();
signals:
    void loginFinishedSignal(bool success);
    void closeSignal();
protected:
    //void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);
private slots:
    void initConnects();
    void loginServer();
    void loginFinished(bool success);
    void showMini();
private:
    Ui::Widget *ui;
    AHttp   *m_http;
    StaticButton    *m_miniButton;
    StaticButton    *m_closeButton;
    StaticButton    *m_loginButton;

};

#endif // WIDGET_H

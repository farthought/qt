#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPaintDevice>
#include <QPainter>
#include <QPaintEngine>

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PAINTWIDGET_H

#include "paintwidget.h"
#include <QPen>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(800,600);
    setWindowTitle("Paint Demo");
}

PaintWidget::~PaintWidget()
{   
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawLine(80,100,650,500);
    painter.setPen(Qt::red);
    painter.drawRect(10,10,100,400);
    painter.setPen(QPen(Qt::green, 5));
    painter.setBrush(Qt::blue);
    painter.drawEllipse(200,150,400,200);
    painter.setPen(QPen(Qt::black,5,Qt::DashDotLine,Qt::RoundCap));
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(50,400,200,150);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black,5,Qt::DashDotLine,Qt::RoundCap));
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(300,400,200,150);

    QLinearGradient linearGradient(60,50,200,200);
    linearGradient.setColorAt(0.2, Qt::white);
    linearGradient.setColorAt(0.6, Qt::green);
    linearGradient.setColorAt(1.0, Qt::black);
    painter.setBrush(QBrush(linearGradient));
    painter.drawEllipse(50,50,200,150);

    QLinearGradient linearGradient1(600,400,800,550);
    linearGradient1.setColorAt(0.2, Qt::white);
    linearGradient1.setColorAt(0.6, Qt::green);
    linearGradient1.setColorAt(1.0, Qt::black);
    painter.setBrush(QBrush(linearGradient1));
    painter.drawEllipse(600,400,200,150);

    QLinearGradient linearGradient2(600,50,200,200);
    linearGradient2.setColorAt(0.2, Qt::white);
    linearGradient2.setColorAt(0.6, Qt::green);
    linearGradient2.setColorAt(1.0, Qt::black);
    painter.setPen(QPen(QBrush(linearGradient2),5));
    painter.drawLine(600,50,200,200);

    QFont font("Courier", 24);
    painter.setFont(font);
    painter.drawText(50, 50, "Hello, world!");
    QTransform transform;
    transform.rotate(+45.0);
    painter.setWorldTransform(transform);
    painter.drawText(60, 60, "Hello, world!");

}

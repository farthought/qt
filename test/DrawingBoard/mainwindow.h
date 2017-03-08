#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>

#include "shape.h"
#include "paintwidget.h"

class MainWindow : public QMainWindow
{
        Q_OBJECT

public:
        MainWindow(QWidget *parent = 0);

signals:
        void changeCurrentShape(Shape::Code newShape);

private slots:
        void drawLineActionTriggered();
        void drawRectActionTriggered();

};

#endif // MAINWINDOW_H

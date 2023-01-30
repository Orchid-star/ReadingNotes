```c++
//.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
};
#endif // MAINWINDOW_H

```

```c++
#include "mainwindow.h"
#include <QRect>
#include <QPainter>
#include <qmath.h>

#define BORDER_WIDTH (7)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(800, 600);
    setContentsMargins(5, 5, 5, 5);
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    int wd = width();
    int ht = height();
    QColor color(241, 72, 76, 10);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < BORDER_WIDTH; i++) {
        QRect rc1(i, i, wd - 1 - i * 2, ht - 1 - i * 2);
        color.setAlpha(qSqrt(i) * 10);
        painter.setBrush(color);
        painter.drawRect(rc1);
    }


    QRect rc2(BORDER_WIDTH, BORDER_WIDTH, wd -BORDER_WIDTH * 2 - 1, ht - BORDER_WIDTH * 2 - 1);
    painter.setBrush(QColor(255, 255, 255, 255));
    painter.drawRect(rc2);

}
```


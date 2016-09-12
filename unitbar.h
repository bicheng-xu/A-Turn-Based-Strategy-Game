#ifndef UNITBAR_H
#define UNITBAR_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QPainter>
#include "mainwindow.h"
#include "unit.h"

class unitbar : public QWidget
{
    Q_OBJECT
public:
    explicit unitbar(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
    void inputunit(unit* a);
    void paintEvent(QPaintEvent *);
private:
    unit *x;
signals:
public slots:
    
};

#endif // UNITBAR_H

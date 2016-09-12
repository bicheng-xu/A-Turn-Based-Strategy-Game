#ifndef CRYSTALGASFOOD_H
#define CRYSTALGASFOOD_H

#include <QWidget>
#include <QLabel>
#include "mainwindow.h"
#include "mapwidget.h"

class crystalgasfood : public QWidget
{
    Q_OBJECT
private:
    QLabel *crystal;
    QLabel *gas;
    QLabel *food;

    QLabel *currentcrystal;
    QLabel *currentgas;
    QLabel *currentfood;
    QLabel *currentmaxfood;
public:
    explicit crystalgasfood(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    
signals:
    
public slots:
};

#endif // CRYSTALGASFOOD_H

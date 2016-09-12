#ifndef PRODUCEUNITWIDGET_H
#define PRODUCEUNITWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "unit.h"

//const double unitX=10,unitY=10,lightGap=400,pixWidth=80,pixHeight=80,blank=25,raceGap=287.5;

class produceunitwidget : public QWidget
{
    Q_OBJECT
private:
    int race;
    int index;
    double getx();
    double gety();
public:
    explicit produceunitwidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void inputraceindex(int i,int j);
signals:
    void produceunit(int i);
public slots:
    
};

#endif // PRODUCEUNITWIDGET_H

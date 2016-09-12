#include "foodadd.h"

foodadd::foodadd(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(0,0,40,40);
}

void foodadd::paintEvent(QPaintEvent *)
{
        double i,j;
    QPainter s(this);
    QPixmap sciencef;
    if (race==0)
    {
        sciencef.load("./image/PBE.gif");
        sciencef=sciencef.scaled(40,40);
        s.drawPixmap(0,0,40,40,sciencef);
    }
    if(race==1)
    {
        sciencef.load("./image/TBS.gif");
        sciencef=sciencef.scaled(40,40);
        s.drawPixmap(0,0,40,40,sciencef);
    }
}

void foodadd::mousePressEvent(QMouseEvent *)
{
    emit foodsig();
}

void foodadd::inputrace(int a)
{
    race=a;
    repaint();
}

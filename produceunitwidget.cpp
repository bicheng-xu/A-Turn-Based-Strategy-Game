#include "produceunitwidget.h"

produceunitwidget::produceunitwidget(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(0,0,40,40);
    race=-1;
}
void produceunitwidget::paintEvent(QPaintEvent *)
{
    double i,j;
    QPainter p(this);
    QPixmap unitmap;
    unitmap.load("./unit-table.gif");
    unitmap=unitmap.scaled(unitmap.width()/2,unitmap.height()/2);
    if(index==16)
    {
        index=1;
        i=getx();
        j=gety();
        index=16;
    }
    else
    {
    i=getx();
    j=gety();
    }
    p.drawPixmap(0,0,unitmap,i,j,40,40);
}

void produceunitwidget::mousePressEvent(QMouseEvent *)
{
    if(race>=0)
        emit produceunit(index);
}

void produceunitwidget::inputraceindex(int i, int j)
{
    race=i;
    index=j;
    repaint();
}

double produceunitwidget::getx()
{
    int tmp;
    tmp=(index-1)%5;
    return (tmp*pixWidth)/2;
}

double produceunitwidget::gety()
{
    int tmp;
    tmp=(index-1)/5;
    return (race*raceGap+tmp*pixHeight+blank)/2;
}

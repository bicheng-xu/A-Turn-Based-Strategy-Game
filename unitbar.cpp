#include "unitbar.h"

unitbar::unitbar(QWidget *parent) :
    QWidget(parent)
{
    x=NULL;
   // setGeometry(0,0,50,50);
}

void unitbar::mousePressEvent(QMouseEvent *)
{
    if(x==NULL){
        return;
    }
    if(x->getselected()==0)
        x->setselected(1);
    else
        x->setselected(0);
    repaint();
}


void unitbar::inputunit(unit* a)
{
    x=a;
}

void unitbar::paintEvent(QPaintEvent *)
{
    if(x!=NULL){
        if(x->getselected()==1){
            QPainter p(this);
            p.setPen(Qt::black);
            p.drawRect(0,0,149,34);
        }
    }
}

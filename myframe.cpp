#include "myframe.h"
#include <QPainter>
#include "mapwidget.h"
#include "game.h"

//const extern qreal linelength=40;
//const extern qreal shortll=sqrt(2)*linelength/2;
//const extern QRect rect(0,0,2*linelength,2*shortll);
extern Game * MainGame;

myframe::myframe(QWidget *parent) :
    QFrame(parent)
{
    times=0.7;
    QRect rect(0,0,2*linelength,2*shortll);
    QPainterPath path;
    QPainter p(this);
    setFrameRect(rect);
    state=0;
    //this->setAttribute(Qt::WA_PaintOutsidePaintEvent);

    unit_table.load("./unit-table.gif");
    qreal width = unit_table.width(); //获得以前图片的宽和高
    qreal height = unit_table.height();
    unit_table=unit_table.scaled(width*times,height*times,Qt::KeepAspectRatio);

    times=0.5;
    P_Base.load("./image/PBN.gif");
    T_Base.load("./image/TBC.gif");
    P_Base=P_Base.scaled(P_Base.width()*times,P_Base.height()*times,Qt::KeepAspectRatio);
    T_Base=T_Base.scaled(T_Base.width()*times,T_Base.height()*times,Qt::KeepAspectRatio);

    times=0.7;

    //QRectF rect = QRectF(0,0,100,100);

    setFrameStyle(NoFrame);
    setAutoFillBackground(true);
    setMouseTracking(true);

    path.moveTo(0,shortll);
    path.lineTo(linelength*0.5,0);
    path.lineTo(linelength*1.5,0);
    path.lineTo(linelength*2,shortll);
    path.lineTo(linelength*1.5,shortll*2);
    path.lineTo(linelength*0.5,shortll*2);
    path.lineTo(0,shortll);

    QPolygon polygon= path.toFillPolygon().toPolygon();//获得这个路径上的所有的点
    QRegion region(polygon);//根据这个点构造这个区域
    setMask(region);
}

void myframe::mouseMoveEvent(QMouseEvent *)
{
    emit MouseMoveon(this);
}

void myframe::moveon()
{
    QPainter p(this);
    QPen pen;
    QPainterPath path;
    path.moveTo(0,shortll);
    path.lineTo(linelength*0.5,0);
    path.lineTo(linelength*1.5,0);
    path.lineTo(linelength*2,shortll);
    path.lineTo(linelength*1.5,shortll*2);
    path.lineTo(linelength*0.5,shortll*2);
    path.lineTo(0,shortll);
    pen.setWidth(4);
    /*switch(state)
    {
    case FOCUSON:
        pen.setColor(Qt::green);
        break;
    case SELECTED:
        pen.setColor(Qt::red);
        break;
    case DONE:
        pen.setColor(Qt::yellow);
        break;
    default:
        break;
    }*/
    pen.setColor(QColor(0x00,0xff,0x00,0x00));

    if(state)
        pen.setColor(Qt::yellow);
    if(ptrToArea->ifselected())
        pen.setColor(Qt::yellow);
    if(ptrToArea->ifselected()&&ptrToArea->getUnits()!=NULL)
    {
        if(ptrToArea->getUnits()->getUnitInfo().omaster()==MainGame->getSelf()->getIndex())
            pen.setColor(Qt::green);
        else
            pen.setColor(Qt::red);
    }
    p.setPen(pen);
    p.drawPath(path);
}

void myframe::paintEvent(QPaintEvent *)
{
    QPalette palette;
    //QPainter p(this);
    //p.setBackgroundMode(Qt::TransparentMode);
    if(!ptrToArea->ifselected())
    {
        if(!ptrToArea->getsight())
        {
            palette.setColor(QPalette::Background,QColor(0,0,0,100));
        }
        else
            palette.setColor(QPalette::Background, QColor(0,0,0,0));
        this->setPalette(palette);
    }
    /*else
    {
        if(ptrToArea->getUnits()->getUnitInfo().omaster()==MainGame->getSelf()->getIndex())
        {
            palette.setColor(QPalette::Background,QColor(0,227,0,100));
        }
    }*/
    if(ptrToArea->getUnits()!=NULL&&ptrToArea->getsight())
    {
        QPainter p(this);
        if(ptrToArea->getUnits()->getUnitInfo().oindex()>0)
        {
        int x=ptrToArea->getUnits()->getUnitInfo().getPixX();
        int y=ptrToArea->getUnits()->getUnitInfo().getPixY();
        p.drawPixmap(10,10,unit_table,x*times,y*times,pixWidth*times,pixHeight*times);
        }
        else
        {
            if(ptrToArea->getUnits()->getUnitInfo().orace()==TERRAN)
                p.drawPixmap(0,0,T_Base,0,0,-1,-1);
            if(ptrToArea->getUnits()->getUnitInfo().orace()==PROTOSS)
                p.drawPixmap(0,0,P_Base,0,0,-1,-1);
        }
    }
    else
    {
    }
    //const unitX=10,unitY=10,lightGap=400,pixWidth=80,pixHeight=80,blank=25,raceGap=287.5;
    /*if(state)
        p.drawPixmap(10,10,unit_table,160*times+temp,25*times,80*times,80*times);
    else
        p.drawPixmap(10,10,unit_table,320*times,(25+2*287.5+80*1)*times,80*times,80*times);
    */
    moveon();
    if(ptrToArea->oreachornot())
    {
        QPalette palette;
        palette.setColor(QPalette::Background,QColor(0,227,0,50));
        this->setPalette(palette);
        //pen.setColor(Qt::green);
    }
    if(ptrToArea->getattackable())
    {
        QPalette palette;
        palette.setColor(QPalette::Background,QColor(227,0,0,50));
        this->setPalette(palette);
        //pen.setColor(Qt::green);
    }
}

void myframe::setstate(int s)
{
    state=s;
}

void myframe::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit SelectaUnit(ptrToArea,LEFT);
    }
    if(event->button() == Qt::RightButton)
    {
        emit SelectaUnit(ptrToArea,RIGHT);
    }
}

int myframe::getstate(int s)
{
    return s;
}

void myframe::MapMoved(int dir)
{
    switch(dir)
    {
    case TOP:
        ptrToArea=ptrToArea->getLink(TOPTOP);
        break;
    case BOTTOM:
        ptrToArea=ptrToArea->getLink(BOTTOMBOTTOM);
        break;
    case LEFT:
        if(ptrToArea->getLink(TOPLEFT))
            ptrToArea=ptrToArea->getLink(TOPLEFT)->getLink(BOTTOMLEFT);
        else
            ptrToArea=ptrToArea->getLink(BOTTOMLEFT)->getLink(TOPLEFT);
        break;
    case RIGHT:
        if(ptrToArea->getLink(TOPRIGHT))
            ptrToArea=ptrToArea->getLink(TOPRIGHT)->getLink(BOTTOMRIGHT);
        else
            ptrToArea=ptrToArea->getLink(BOTTOMRIGHT)->getLink(TOPRIGHT);
        break;
    default:
        break;
    }
}

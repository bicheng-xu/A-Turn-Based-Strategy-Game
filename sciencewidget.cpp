#include "sciencewidget.h"

extern Game *MainGame;
sciencewidget::sciencewidget(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(0,0,40,40);
    index=1;
    /*if(!MainGame->getSelf()->checkTechBase(index))
    setornot=0;
    if(MainGame->getSelf()->checkTechBase(index))
    setornot=1;
    */
}

void sciencewidget::paintEvent(QPaintEvent *)
{
    double i,j;
    QPainter s(this);
    QPixmap sciencef;
    if (race==0&&index==1)
    {
        sciencef.load("./image/PBG.gif");
        sciencef=sciencef.scaled(40,40);
        s.drawPixmap(0,0,40,40,sciencef);
    }
    if (race==0&&index==2)
    {
        sciencef.load("./image/PBR.gif");
        sciencef=sciencef.scaled(40,40);
        s.drawPixmap(0,0,40,40,sciencef);

    }
    if (race==0&&index==3)
    {
        sciencef.load("./image/PVR.gif");
        sciencef=sciencef.scaled(40,40);
        s.drawPixmap(0,0,40,40,sciencef);

    }
    if (race==1&&index==1)
    {
        sciencef.load("./image/TBB.gif");
        sciencef=sciencef.scaled(40,40);
        s.drawPixmap(0,0,40,40,sciencef);
    }
    if (race==1&&index==2)
    {
        sciencef.load("./image/TBG.gif");
        sciencef=sciencef.scaled(40,40);
        s.drawPixmap(0,0,40,40,sciencef);
    }
    if (race==1&&index==3)
    {
        sciencef.load("./image/TVF.gif");
        sciencef=sciencef.scaled(40,40);
        s.drawPixmap(0,0,40,40,sciencef);
    }
    if (race==1&&index==4)
    {
        sciencef.load("./image/TBG.gif");
        sciencef=sciencef.scaled(40,40);
        s.drawPixmap(0,0,40,40,sciencef);
    }
    Player *tmp;
    if(MainGame->getSelf()->getRace()==race)
        tmp=MainGame->getSelf();
    else
        tmp=MainGame->getEnemy();
    //if (setornot==1)
    if(tmp->getTechStatus(index-1))
    {
        QPainter p(this);
        p.setPen(Qt::black);
        p.drawRect(0,0,39,39);
    }
    /*if(tmp->checkTechBase(index-1))
    {
        setEnabled(true);
        setVisible(true);
    }
    else
    {
        setEnabled(false);
        setVisible(false);
    }*/
}

void sciencewidget::mousePressEvent(QMouseEvent *)
{
    int i;
    if(MainGame->getSelf()->getIndex()==MainGame->getTurn())
    if(MainGame->getSelf()->checkTechBase(index-1))
    if(MainGame->getSelf()->getCrystal()>=MainGame->getSelf()->getTechCrystalCost(index-1))
    {
        if(MainGame->getSelf()->getGas()>=MainGame->getSelf()->getTechGasCost(index-1))
        {
            MainGame->getSelf()->researchTech(index-1);
            i=MainGame->getSelf()->getTechCrystalCost(index-1);
            i=-i;
            MainGame->getSelf()->incCrystal(i);
            i=MainGame->getSelf()->getTechGasCost(index-1);
            i=-i;
            MainGame->getSelf()->incGas(i);
            setornot=1;
            emit sciencesig(index);
            repaint();
        }
    }
}

void sciencewidget::inputraceindex(int i, int j)
{
    race=i;
    index=j;
    repaint();
}

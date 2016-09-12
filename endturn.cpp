#include "endturn.h"

extern Game *MainGame;
endturn::endturn(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(MapWidth+RightTabWidth/2-100,RightTabHeight-40,80,20);

    endturnb=new QPushButton(this);
    endturnb->setText("End Turn");
    endturnb->setGeometry(0,0,80,20);
    if(MainGame->getSelf()->getIndex()==MainGame->getTurn())
        setEnabled(true);
    else
        setEnabled(false);

    connect(endturnb,SIGNAL(clicked()),this,SLOT(reendturn()));
}

void endturn::reendturn()
{
    emit seendturn();
}

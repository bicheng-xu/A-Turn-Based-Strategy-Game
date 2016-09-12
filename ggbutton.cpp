#include "ggbutton.h"

extern Game *MainGame;
ggButton::ggButton(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(MapWidth+RightTabWidth/2+20,RightTabHeight-80,80,20);

    ggbutton=new QPushButton(this);
    ggbutton->setText("Surrender.");
    ggbutton->setGeometry(0,0,80,20);

    if(MainGame->getSelf()->getIndex()==MainGame->getTurn())
        setEnabled(true);
    else
        setEnabled(false);

    connect(ggbutton,SIGNAL(clicked()),this,SLOT(regg()));
}

void ggButton::regg()
{
    emit segg();
}

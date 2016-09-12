#include "crystalgasfood.h"

extern Game *MainGame;
crystalgasfood::crystalgasfood(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(WindowWidth-RightTabWidth,2,RightTabWidth,50);
    setAutoFillBackground(true);

    crystal=new QLabel(this);
    crystal->setGeometry(10,0,200,RightTabHeight/25);
    crystal->setText("Crystal");

    gas=new QLabel(this);
    gas->setGeometry(90,0,200,RightTabHeight/25);
    gas->setText("Gas");

    food=new QLabel(this);
    food->setGeometry(150,0,200,RightTabHeight/25);
    food->setText("Food");

    currentcrystal=new QLabel(this);
    currentcrystal->setGeometry(10,RightTabHeight/40,200,RightTabHeight/25);
    currentcrystal->setVisible(1);

    currentgas=new QLabel(this);
    currentgas->setGeometry(90,RightTabHeight/40,200,RightTabHeight/25);
    currentgas->setVisible(1);

    currentfood=new QLabel(this);
    currentfood->setGeometry(150,RightTabHeight/40,200,RightTabHeight/25);
    currentfood->setVisible(1);
}

void crystalgasfood::paintEvent(QPaintEvent *)
{
    int crystal,gas,maxfood,currentfoodi;
    if(MainGame==NULL){
        currentcrystal->setText("");
        currentcrystal->setVisible(0);
        currentgas->setText("");
        currentgas->setVisible(0);
        currentfood->setText("");
        currentfood->setVisible(0);
    }
    else{
        crystal=MainGame->getSelf()->getCrystal();
        gas=MainGame->getSelf()->getGas();
        maxfood=MainGame->getSelf()->getMaxFood();
        currentfoodi=MainGame->getSelf()->getCurrentFood();

        QString scrystal;
        QString sgas;
        QString sfood;
        QString temp;

        scrystal=QString::number(crystal);
        sgas=QString::number(gas);

        sfood=QString::number(currentfoodi);
        temp="/";
        sfood=sfood+temp;
        temp=QString::number(maxfood);
        sfood=sfood+temp;

        currentcrystal->setText(scrystal);
        currentgas->setText(sgas);
        currentfood->setText(sfood);
    }
}

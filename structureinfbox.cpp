#include "structureinfbox.h"

extern DataBase Data;
extern Game *MainGame;
structureinfbox::structureinfbox(QWidget *parent) :
    QWidget(parent)
{
    WorkerOnCrystal=0;
    WorkerOnGas=0;

    setGeometry(::WindowWidth-::RightTabWidth,5,::RightTabWidth,::RightTabHeight);

    status=new QLabel(this);
    status->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*1+RightTabHeight/30,200,RightTabHeight/13);
    status->setText("Status");

    name=new QLabel(this);
    name->setGeometry(10,RightTabHeight/30,200,RightTabHeight/13);
    name->setText("Sturcture Information:");

    health=new QLabel(this);
    health->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*2+RightTabHeight/30,200,RightTabHeight/13);
    health->setText("Maxhealth:");

    healthc=new QLabel(this);
    healthc->setGeometry(10+RightTabWidth/5*3,RightTabWidth/5*2+RightTabHeight/25*2+RightTabHeight/30,200,RightTabHeight/13);
    healthc->setText("-");

    shield=new QLabel(this);
    shield->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*3+RightTabHeight/30,200,RightTabHeight/13);
    shield->setText("Shield:");

    shieldc=new QLabel(this);
    shieldc->setGeometry(10+RightTabWidth/5*3,RightTabWidth/5*2+RightTabHeight/25*3+RightTabHeight/30,200,RightTabHeight/13);
    shieldc->setText("-");

    def=new QLabel(this);
    def->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*4+RightTabHeight/30,200,RightTabHeight/13);
    def->setText("Defense:");

    defc=new QLabel(this);
    defc->setGeometry(10+RightTabWidth/5*3,RightTabWidth/5*2+RightTabHeight/25*4+RightTabHeight/30,200,RightTabHeight/13);
    defc->setText("-");

    int i,j;

    pbar[0]=new QProgressBar(this);
    pbar[0]->setGeometry(RightTabWidth/2-20,RightTabWidth/5*2+RightTabHeight/25+RightTabHeight/30+20,90,10);
    pbar[0]->setVisible(0);

    pbar[1]=new QProgressBar(this);
    pbar[1]->setGeometry(RightTabWidth/2-20,RightTabWidth/5*2+RightTabHeight/25+RightTabHeight/30+30,90,10);
    pbar[1]->setVisible(0);

    pbar[2]=new QProgressBar(this);
    pbar[2]->setGeometry(RightTabWidth/2-20,RightTabWidth/5*2+RightTabHeight/25+RightTabHeight/30+25,90,10);
    pbar[2]->setMaximum(100);
    pbar[2]->setValue(40);
    pbar[2]->setVisible(0);

    produceq=new QLabel(this);
    produceq->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*6+RightTabHeight/30,200,RightTabHeight/13);
    produceq->setText("Production queue:");

    sciencet=new QLabel(this);
    sciencet->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*7+RightTabHeight/30+10+45*4,200,RightTabHeight/13);
    sciencet->setText("Science and technology:");

    workernumber=new QLabel(this);
    workernumber->setGeometry(10,int(RightTabWidth/5*2+RightTabHeight/25*8+RightTabHeight/30*2.5+10+45*4),200,RightTabHeight/13);
    workernumber->setText("Worker Number:");

    gasnumber=new QLabel(this);
    gasnumber->setGeometry(10,int(RightTabWidth/5*2+RightTabHeight/25*8+RightTabHeight/30*3.5+10+45*4),200,RightTabHeight/13);
    gasnumber->setText("-");

    crystalnumber=new QLabel(this);
    crystalnumber->setGeometry(10+RightTabWidth/5*3-20,int(RightTabWidth/5*2+RightTabHeight/25*8+RightTabHeight/30*3.5+10+45*4),200,RightTabHeight/13);
    crystalnumber->setText("-");

    for(i=0;i<=3;i++)
        for(j=0;j<=3;j++)
            if(i!=3||j!=3)
            {
                produce[i][j]=new produceunitwidget(this);
                connect(produce[i][j],SIGNAL(produceunit(int)),this,SLOT(clickProduce(int)));
            }
    produce[3][3]=new produceunitwidget(this);
    connect(produce[3][3],SIGNAL(produceunit(int)),this,SLOT(clickProduce(int)));

    for(i=0;i<=3;i++)
    {
        science[i]=new sciencewidget(this);
        science[i]->setGeometry(10+45*i,int(RightTabWidth/5*2+RightTabHeight/25*8+RightTabHeight/30*1.5+10+45*4),40,40);
        connect(science[i],SIGNAL(sciencesig(int)),this,SLOT(clickResearch(int)));
    }

    foodadd1=new foodadd(this);
    foodadd1->setGeometry(10+45*4,int(RightTabWidth/5*2+RightTabHeight/25*8+RightTabHeight/30*1.5+10+45*4),40,40);

    connect(foodadd1,SIGNAL(foodsig()),this,SLOT(clickAddFood()));
    /*i=2;
    for(j=0;j<i;j++){
            pbar[i]=new QProgressBar(this);
            pbar[i]->setMaximum(101);
            pbar[i]->setMinimum(0);
            pbar[i]->setValue(40);
            pbar[i]->setGeometry(75,RightTabWidth/5*2+RightTabHeight/25*1+RightTabHeight/30-5+i*10,70,10);
            pbar[i]->setVisible(0);
    }

    ztbar=new QProgressBar(this);
    ztbar->setMaximum(101);
    ztbar->setMinimum(0);
    ztbar->setValue(40);
    ztbar->setGeometry(75,RightTabWidth/5*2+RightTabHeight/25*1+RightTabHeight/30,70,10);
    ztbar->setVisible(1);*/
}

void structureinfbox::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap((RightTabWidth-RightTabWidth/4*2)/2+20,RightTabHeight/25+RightTabHeight/30+20,map,0,0,-1,-1);
}

void structureinfbox::restructureinf(area* stru){
    int i,j;

    str=stru;

    if(stru!=NULL&&stru->getUnits()!=NULL&&stru->getUnits()->getUnitInfo().oindex()>0)
        stru=NULL;
    if(stru==NULL){
        setEnabled(false);
        setVisible(false);
        healthc->setText("-");
        shieldc->setText("-");
        defc->setText("-");
        pbar[1]->setVisible(0);
        pbar[2]->setVisible(0);
        pbar[2]->setVisible(0);
        for(i=0;i<=3;i++)
            for(j=0;j<=3;j++)
                //if(i!=3||j!=3)
                produce[i][j]->inputraceindex(-5,-5);
        crystalnumber->setText("-");
        gasnumber->setText("-");
    }
    else if(stru->getUnits()!=NULL){
        setEnabled(true);
        setVisible(true);

        WorkerOnCrystal=0;
        WorkerOnGas=0;
        for(std::vector<unit>::iterator iter=stru->getUnits()->getUnitShell()->begin()+1;iter<stru->getUnits()->getUnitShell()->end();iter++)
        {
            if(iter->getworkplace()==CRYSTAL)
                WorkerOnCrystal++;
            else
                WorkerOnGas++;
        }
        crystalnumber->setText(QString::number(WorkerOnCrystal,10));
        gasnumber->setText(QString::number(WorkerOnGas,10));

        /*
        QString str1;
        QString str2;
        str1="Gas:";
        str2=QString::number(         duankou          );
        str1=str1+str2;
        gasnumber->setText(str1);

        str1="Crystal:"
        str2=QString::number(         duankou          );
        str1=str1+str2;
        crystalnumber->setText(str1);
        */
        unit tempstru;
        tempstru=stru->getUnits()->getUnitInfo();

        int tempa;
        QString tempstring;

        tempa=tempstru.ohealthmax();
        tempstring=QString::number(tempa);
        healthc->setText(tempstring);

        tempa=tempstru.oshieldmax();
        tempstring=QString::number(tempa);
        shieldc->setText(tempstring);

        tempa=tempstru.odef();
        tempstring=QString::number(tempa);
        defc->setText(tempstring);

        if(tempstru.orace()==PROTOSS){
            pbar[1]->setMaximum(tempstru.ohealthmax());
            pbar[1]->setValue(tempstru.ohealthcurrent());
            pbar[1]->setVisible(true);
            pbar[0]->setMaximum(tempstru.oshieldmax());
            pbar[0]->setValue(tempstru.oshieldcurrent());
            pbar[0]->setVisible(true);
            pbar[2]->setVisible(false);
        }
        if(tempstru.orace()==ZERG||tempstru.orace()==TERRAN){
            pbar[2]->setMaximum(tempstru.ohealthmax());
            pbar[2]->setValue(tempstru.ohealthcurrent());
            pbar[2]->setVisible(true);
            pbar[0]->setVisible(false);
            pbar[1]->setVisible(false);
        }

        if(tempstru.orace()==PROTOSS)
        {
        map.load("./image/PBN.gif");
        foodadd1->inputrace(0);
        }
        if(tempstru.orace()==TERRAN)
        {
        map.load("./image/TBC.gif");
        foodadd1->inputrace(1);
        }
        /*if(tempstru->orace()==ZERG)
        map.load("./ZergStructure.jpg");
*/
        map=map.scaled(map.width()*0.8,map.height()*0.8);
        Player *tmpplayer;
        if(stru->getUnits()->getUnitInfo().omaster()==MainGame->getSelf()->getIndex())
            tmpplayer=MainGame->getSelf();
        else
            tmpplayer=MainGame->getEnemy();
        for(i=0;i<=3;i++){
            for(j=0;j<=3;j++)
                if(i!=3||j!=3){
                produce[i][j]->setGeometry(10+(j)*(5+40),RightTabWidth/5*2+RightTabHeight/25*8+RightTabHeight/30+RightTabHeight/40+10+(i-1)*(5+40),40,40);
                produce[i][j]->inputraceindex(tempstru.orace(),i*4+j+1);
                if(Data.getUnit(tempstru.orace(),i*4+j+1).oindex()!=-1111&&tmpplayer->checkUnitTech(i*4+j+1))
                {
                    produce[i][j]->setEnabled(true);
                    produce[i][j]->setVisible(true);
                }
                else
                {
                    produce[i][j]->setEnabled(false);
                    produce[i][j]->setVisible(false);
                }
            }
        }
        produce[3][3]->setGeometry(10+(3)*(5+40),RightTabWidth/5*2+RightTabHeight/25*8+RightTabHeight/30+RightTabHeight/40+10+(3-1)*(5+40),40,40);
        produce[3][3]->inputraceindex(tempstru.orace(),3*4+3+1);

        for(i=0;i<=3;i++)
        {
            science[i]->inputraceindex(tempstru.orace(),i+1);
        }
    }
    repaint();
}


void structureinfbox::clickResearch(int ind)
{
    restructureinf(str);
    emit Research(ind);
}

void structureinfbox::clickProduce(int ind)
{
    emit Produce(ind);
}

void structureinfbox::clickAddFood()
{
    emit AddFood();
}

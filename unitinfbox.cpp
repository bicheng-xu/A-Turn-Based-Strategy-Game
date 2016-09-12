#include "unitinfbox.h"
#include <vector>
#include <QTextCodec>

using std::vector;

Unitinfbox::Unitinfbox(QWidget *parent) :
    QWidget(parent)
{
    arar=NULL;
    setGeometry(WindowWidth-RightTabWidth,5,RightTabWidth,RightTabHeight);
   // setAutoFillBackground(true);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));


/*
    QLabel *label;
    QLabel *name;
    QLabel *unitname;
    QLabel *maxhealth;
    QLabel *unitmaxhealth;
    QLabel *damage;
    QLabel *unitdamage;
    QLabel *clowdown;
    QLabel *unitclowdown;
    QLabel *damagetype;
    QLabel *unitdamagetype;
    QLabel *armor;
    QLabel *unitarmor;
    QLabel *maxmana;
    QLabel *unitmana;
*/

  /*  crystal=new QLabel(this);
    crystal->setGeometry(10,0,200,RightTabHeight/13);
    crystal->setText("Crystal");

    gas=new QLabel(this);
    gas->setGeometry(90,0,200,RightTabHeight/13);
    gas->setText("Gas");

    food=new QLabel(this);
    food->setGeometry(150,0,200,RightTabHeight/13);
    food->setText("Food");*/

    label=new QLabel(this);
    label->setGeometry(10,RightTabHeight/30,200,RightTabHeight/13);
    label->setText("Unit Information:");

    name=new QLabel(this);
    name->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25+RightTabHeight/30,200,RightTabHeight/13);
    name->setText("Unit name:");

    unitname=new QLabel(this);
    unitname->setGeometry(10+RightTabWidth/5*3,RightTabWidth/5*2+RightTabHeight/25+RightTabHeight/30,200,RightTabHeight/13);
    unitname->setText("-");

    maxhealth=new QLabel(this);
    maxhealth->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*2+RightTabHeight/30,200,RightTabHeight/13);
    maxhealth->setText("Max HP:");

    unitmaxhealth=new QLabel(this);
    unitmaxhealth->setGeometry(10+RightTabWidth/5*3,RightTabWidth/5*2+RightTabHeight/25*2+RightTabHeight/30,200,RightTabHeight/13);
    unitmaxhealth->setText("-");

    maxmana=new QLabel(this);
    maxmana->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*3+RightTabHeight/30,200,RightTabHeight/13);
    maxmana->setText("Max MP:");

    unitmana=new QLabel(this);
    unitmana->setGeometry(10+RightTabWidth/5*3,RightTabWidth/5*2+RightTabHeight/25*3+RightTabHeight/30,200,RightTabHeight/13);
    unitmana->setText("-");

    damage=new QLabel(this);
    damage->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*4+RightTabHeight/30,200,RightTabHeight/13);
    damage->setText("Damage:");

    unitdamage=new QLabel(this);
    unitdamage->setGeometry(10+RightTabWidth/5*3,RightTabWidth/5*2+RightTabHeight/25*4+RightTabHeight/30,200,RightTabHeight/13);
    unitdamage->setText("-");

    clowdown=new QLabel(this);
    clowdown->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*5+RightTabHeight/30,200,RightTabHeight/13);
    clowdown->setText("Clowdown:");

    unitclowdown=new QLabel(this);
    unitclowdown->setGeometry(10+RightTabWidth/5*3,RightTabWidth/5*2+RightTabHeight/25*5+RightTabHeight/30,200,RightTabHeight/13);
    unitclowdown->setText("-");

    damagetype=new QLabel(this);
    damagetype->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*6+RightTabHeight/30,200,RightTabHeight/13);
    damagetype->setText("Damagetype:");

    unitdamagetype=new QLabel(this);
    unitdamagetype->setGeometry(10+RightTabWidth/5*3,RightTabWidth/5*2+RightTabHeight/25*6+RightTabHeight/30,200,RightTabHeight/13);
    unitdamagetype->setText("-");

    armor=new QLabel(this);
    armor->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*7+RightTabHeight/30,200,RightTabHeight/13);
    armor->setText("Armor:");

    unitarmor=new QLabel(this);
    unitarmor->setGeometry(10+RightTabWidth/5*3,RightTabWidth/5*2+RightTabHeight/25*7+RightTabHeight/30,200,RightTabHeight/13);
    unitarmor->setText("-");

    skills=new QLabel(this);
    skills->setGeometry(10,RightTabWidth/5*2+RightTabHeight/25*8+RightTabHeight/30,200,RightTabHeight/13);
    skills->setText("Skills:");

    queuelabel=new QLabel(this);
    queuelabel->setGeometry(10,RightTabHeight/2+RightTabHeight/25*0+RightTabHeight/30,200,RightTabHeight/13);
    queuelabel->setText("Queue Information:");

    //QPalette palette1;
    //palette1.setColor();
    //palette1.setColor(palette1::Background,QColor(Qt::blue));

    int i=6;
    int j;
    int k=2;
    int w;

    for(j=0;j<i;j++){
        UnitLabel[j]=new QLabel(this);
        UnitLabel[j]->setGeometry(20,RightTabHeight/2+RightTabHeight/20*(j+1)+RightTabHeight/30,200,RightTabHeight/13);
        QString str1="Unit ";
        QString str2=QString::number(j+1);
        QString str3=str1+str2;
        UnitLabel[j]->setText(str3);
        /*progressbar[j]->setStyleSheet("\
                           QProgressBar::chunk{\
                            background:blue;\
                            margin:1.0px;\
                            height:3px;\
                           }\
                           QProgressBar{\
                           border:6px solid red;\
                            background:black\
                           }\
    ");*/
        progressbar[j]=new QProgressBar(this);
        progressbar[j]->setMaximum(101);
        progressbar[j]->setMinimum(0);
        progressbar[j]->setValue(40);
        progressbar[j]->setGeometry(75,RightTabHeight/2+RightTabHeight/20*(j+1)+RightTabHeight/30*2,70,10);
        progressbar[j]->setVisible(0);

    }

    k=2;
    for(j=0;j<i;j++){
        for(w=0;w<k;w++){
            progressbar1[j][w]=new QProgressBar(this);
            progressbar1[j][w]->setMaximum(101);
            progressbar1[j][w]->setMinimum(0);
            progressbar1[j][w]->setValue(40);
            progressbar1[j][w]->setGeometry(75,RightTabHeight/2+RightTabHeight/20*(j+1)+RightTabHeight/30*2-5+w*10,70,10);
            progressbar1[j][w]->setVisible(0);
        }
    }

    k=3;
    for(j=0;j<i;j++){
        for(w=0;w<k;w++){
            progressbar2[j][w]=new QProgressBar(this);
            progressbar2[j][w]->setMaximum(101);
            progressbar2[j][w]->setMinimum(0);
            progressbar2[j][w]->setValue(40);
            progressbar2[j][w]->setGeometry(75,RightTabHeight/2+RightTabHeight/20*(j+1)+RightTabHeight/30*2-10+w*10,70,10);
            progressbar2[j][w]->setVisible(0);
        }
    }

    //areatemp=NULL;

    int q=0;
    for(q;q<6;q++){
        selectstatus[q]=0;
    }

    for(q=0;q<6;q++){
    unitbarshell[q]=new unitbar(this);
    unitbarshell[q]->setGeometry(15,RightTabHeight/2+RightTabHeight/20*(q+1)+RightTabHeight/30+12,150,35);
    }

    //connect(this,SIGNAL(cl(int)),this,SLOT(re(int)));
}

void Unitinfbox::paintEvent(QPaintEvent *){
    int currenthigh;

    QPalette palette;
    palette.setColor(QPalette::Background,QColor(Qt::white));
    setPalette(palette);


    //int x=ptrToArea->getUnits()->getUnitInfo().getPixX();
    //int y=ptrToArea->getUnits()->getUnitInfo().getPixY();
    //p.drawPixmap(10,10,unit_table,x*times,y*times,pixWidth*times,pixHeight*times);


    // !!!!!!!!!!

    QPainter p(this);
    QPixmap map;
    map.load("./unit-table.gif");
    if(arar!=NULL){
    int x=arar->getUnits()->getUnitInfo().getPixX();
    int y=arar->getUnits()->getUnitInfo().getPixY();
    double times=1.5;
    map=map.scaled(map.width()*times,map.height()*times,Qt::KeepAspectRatio);
    //map=map.scaled(10*RightTabWidth/4*2,10*RightTabWidth/4*2,Qt::KeepAspectRatio);
    //p.drawPixmap((RightTabWidth-RightTabWidth/4*2)/2+20,RightTabHeight/25+RightTabHeight/30+20,map,RightTabWidth/4*2,RightTabWidth/4*2,x,y);
    p.drawPixmap((RightTabWidth-RightTabWidth/4*2)/2+20,RightTabHeight/25+RightTabHeight/30+20,map,x*times,y*times,RightTabWidth/4*2-10,RightTabWidth/4*2-10);
    }

   /* QPainter p(this);
    QPixmap map;
    map.load("./3.png");
    map=map.scaled(RightTabWidth/4*2,RightTabWidth/4*2,Qt::KeepAspectRatio);
    p.drawPixmap((RightTabWidth-RightTabWidth/4*2)/2,RightTabHeight/25+RightTabHeight/30,map,0,0,-1,-1);

    currenthigh=40+RightTabWidth/3*2;*/

    int q=0;
    if(arar!=NULL)
        q=arar->getUnits()->getUnitNum();
    for(int i=0;i<q;i++){
        //if(selectstatus[q]==1){
        if((arar->getUnits()->getUnitShell()->begin()+i)->getselected()){
            //p.drawRect(15,RightTabHeight/2+RightTabHeight/20*(i+1)+RightTabHeight/30+12,150,35);
        }
    }
}

void Unitinfbox::re(area* ar)
{

    int i=6;
    int j;
    int k=2;
    int w;
    arar=ar;

        for(j=0;j<i;j++){
             progressbar[j]->setVisible(0);
        }

        k=2;
        for(j=0;j<i;j++){
            for(w=0;w<k;w++){
                progressbar1[j][w]->setVisible(0);
            }
        }

        k=3;
        for(j=0;j<i;j++){
            for(w=0;w<k;w++){
                progressbar2[j][w]->setVisible(0);
            }
        }
        QString str="-";
        unitname->setText(str);

        unitmaxhealth->setText(str);

        unitdamage->setText(str);

        unitclowdown->setText(str);

        unitdamagetype->setText(str);

        unitarmor->setText(str);

        unitmana->setText(str);

        for(int j=0;j<6;j++)
            unitbarshell[j]->inputunit(NULL);

    if(ar!=NULL&&ar->getUnits()!=NULL&&ar->getUnits()->getUnitInfo().oindex()<0)
        ar=NULL;
    if(ar==NULL)
    {
        setEnabled(false);
        setVisible(false);
       /* for(j=0;j<i;j++){
             progressbar[j]->setVisible(0);
        }

        k=2;
        for(j=0;j<i;j++){
            for(w=0;w<k;w++){
                progressbar1[j][w]->setVisible(0);
            }
        }

        k=3;
        for(j=0;j<i;j++){
            for(w=0;w<k;w++){
                progressbar2[j][w]->setVisible(0);
            }
        }
        QString str="-";
        unitname->setText(str);

        unitmaxhealth->setText(str);

        unitdamage->setText(str);

        unitclowdown->setText(str);

        unitdamagetype->setText(str);

        unitarmor->setText(str);

        unitmana->setText(str);

        for(int j=0;j<6;j++)
            unitbarshell[j]->inputunit(NULL);
            */
    }
    else if(ar->getUnits()!=NULL)
    {
        setEnabled(true);
        setVisible(true);
        QString str;
        std::vector<unit> *p=ar->getUnits()->getUnitShell();
        str=QString::fromStdString(p->begin()->oname());
        unitname->setText(str);

        str=QString::number(p->begin()->ohealthmax());
        unitmaxhealth->setText(str);

        str=QString::number(p->begin()->olandstr());
        unitdamage->setText(str);

        str=QString::number(p->begin()->olandstrspeed());
        unitclowdown->setText(str);

        str=QString::number(p->begin()->olandstrtype());
        unitdamagetype->setText(str);

        str=QString::number(p->begin()->odef());
        unitarmor->setText(str);

        str=QString::number(p->begin()->odeftype());
        unitmana->setText(str);

        //Group Information



        if(p->begin()->orace()==TERRAN||p->begin()->orace()==ZERG){
            if(p->begin()->omanamax()!=0){
                i=ar->getUnits()->getUnitNum();
                for(j=0;j<i;j++){
                    progressbar1[j][0]->setMaximum((p->begin()+j)->ohealthmax());
                    progressbar1[j][0]->setValue((p->begin()+j)->ohealthcurrent());
                    progressbar1[j][0]->setVisible(1);
                    progressbar1[j][1]->setMaximum((p->begin()+j)->omanamax());
                    progressbar1[j][1]->setValue((p->begin()+j)->omanacurrent());
                    progressbar1[j][1]->setVisible(1);
                }
            }
            if(p->begin()->omanamax()==0){
                i=ar->getUnits()->getUnitNum();
                for(j=0;j<i;j++){
                    progressbar[j]->setMaximum((p->begin()+j)->ohealthmax());
                    progressbar[j]->setValue((p->begin()+j)->ohealthcurrent());
                    progressbar[j]->setVisible(1);
                }
            }
        }

        if(p->begin()->orace()==PROTOSS){
            if(p->begin()->omanamax()!=0){
                i=ar->getUnits()->getUnitNum();
                for(j=0;j<i;j++){
                    progressbar2[j][1]->setMaximum((p->begin()+j)->ohealthmax());
                    progressbar2[j][1]->setValue((p->begin()+j)->ohealthcurrent());
                    progressbar2[j][1]->setVisible(1);
                    progressbar2[j][0]->setMaximum((p->begin()+j)->oshieldmax());
                    progressbar2[j][0]->setValue((p->begin()+j)->oshieldcurrent());
                    progressbar2[j][0]->setVisible(1);
                    progressbar2[j][2]->setMaximum((p->begin()+j)->omanamax());
                    progressbar2[j][2]->setValue((p->begin()+j)->omanacurrent());
                    progressbar2[j][2]->setVisible(1);
                }
            }
            if(p->begin()->omanamax()==0){
                i=ar->getUnits()->getUnitNum();
                for(j=0;j<i;j++){
                    int pp=p->begin()->ohealthmax();
                    progressbar1[j][1]->setMaximum(50);
                    progressbar1[j][1]->setMaximum((p->begin()+j)->ohealthmax());
                    progressbar1[j][1]->setValue((p->begin()+j)->ohealthcurrent());
                    progressbar1[j][1]->setVisible(1);
                    progressbar1[j][0]->setMaximum((p->begin()+j)->oshieldmax());
                    progressbar1[j][0]->setValue((p->begin()+j)->oshieldcurrent());
                    progressbar1[j][0]->setVisible(1);
                }
            }
        }

        i=ar->getUnits()->getUnitNum();
        for(j=0;j<i;j++){
            unitbarshell[j]->inputunit(&*(p->begin()+j));
        }
       /* for(;j<6;j++)
        {
            unitbarshell[j]->inputunit(NULL);
        }*/

        i=ar->getUnits()->getUnitNum();
        for(j=0;j<i;j++){
            (p->begin()+j)->setselected(1);
            selectstatus[j]=(p->begin()+j)->getselected();
        }
    }
    repaint();
}

void Unitinfbox::mousePressEvent(QMouseEvent *)
{
    static int p=0;
    //emit cl(p);
}

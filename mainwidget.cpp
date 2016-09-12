#include "mainwidget.h"
extern Game *MainGame;
extern TcpNet *Network;
extern DataBase Data;

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    //MainGame=new Game(OFFLINE);
    MainGame=new Game();
    //Network=new TcpNet(this);

    //selectedarea=NULL;

    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    setGeometry(0,0,WindowWidth,WindowHeight);
    MapWidget=new mapwidget(this);
    ConstructureInfoBox=new structureinfbox(this);
    UnitInfoWidget=new Unitinfbox(this);
    ResourceInfoBox=new crystalgasfood(this);
    EndTurnButton=new class endturn(this);
    GgButton=new QPushButton(this);
    GgButton->setText("Surrender");
    GgButton->setGeometry(MapWidth+RightTabWidth/2+20,RightTabHeight-40,80,20);
    BuildBase=new QPushButton(this);
    BuildBase->setText("Build New Base");
    BuildBase->setGeometry(MapWidth+RightTabWidth/2-50,RightTabHeight-500,100,50);
    BuildBase->setEnabled(false);
    BuildBase->setVisible(false);
    //QPalette palette;
    //setAutoFillBackground(true);
    //palette.setColor(QPalette::Background,QColor(Qt::blue));
    //setPalette(palette);

    ConstructureInfoBox->setEnabled(false);
    UnitInfoWidget->setEnabled(false);
    ConstructureInfoBox->setVisible(false);
    UnitInfoWidget->setVisible(false);


    //Sound=new Widget(this);
    //Sound->setVisible(false);

    MapMoveWidget *LeftPad=new MapMoveWidget(this,LEFT),*RightPad=new MapMoveWidget(this,RIGHT),*TopPad=new MapMoveWidget(this,TOP),*BottomPad=new MapMoveWidget(this,BOTTOM);
    LeftPad->setGeometry(0,0,PadWidth,WindowHeight);
    RightPad->setGeometry(WindowWidth-PadWidth,0,PadWidth,WindowHeight);
    TopPad->setGeometry(0,0,WindowWidth,PadWidth);
    BottomPad->setGeometry(0,WindowHeight-PadWidth,WindowWidth,PadWidth);
    QObject::connect(LeftPad,SIGNAL(MoveMap(int)),MapWidget,SLOT(MapMoved(int)));
    QObject::connect(RightPad,SIGNAL(MoveMap(int)),MapWidget,SLOT(MapMoved(int)));
    QObject::connect(TopPad,SIGNAL(MoveMap(int)),MapWidget,SLOT(MapMoved(int)));
    QObject::connect(BottomPad,SIGNAL(MoveMap(int)),MapWidget,SLOT(MapMoved(int)));

    connect(MapWidget,SIGNAL(UnitSelected(area*)),this,SLOT(display(area*)));
    connect(MapWidget,SIGNAL(UnitSelected(area*)),UnitInfoWidget,SLOT(re(area*)));
    connect(EndTurnButton,SIGNAL(seendturn()),this,SLOT(endturn()));
    connect(MapWidget,SIGNAL(UnitSelected(area*)),ConstructureInfoBox,SLOT(restructureinf(area*)));
    connect(ConstructureInfoBox,SIGNAL(Produce(int)),MapWidget,SLOT(ProduceUnit(int)));
    connect(ConstructureInfoBox,SIGNAL(Research(int)),this,SLOT(Research(int)));
    connect(ConstructureInfoBox,SIGNAL(AddFood()),this,SLOT(BuileFood()));
    connect(BuildBase,SIGNAL(clicked()),MapWidget,SLOT(BuildNewBase()));

    connect(MapWidget,SIGNAL(refresh()),this,SLOT(refresh()));

    /*connect(MapWidget,SIGNAL(PlaySound(int,int,int)),Sound,SLOT(PlaySystemSound(int,int,int)));
    connect(ConstructureInfoBox->science[0],SIGNAL(PlaySound(int,int,int)),Sound,SLOT(PlaySystemSound(int,int,int)));
    connect(ConstructureInfoBox->science[1],SIGNAL(PlaySound(int,int,int)),Sound,SLOT(PlaySystemSound(int,int,int)));
    connect(ConstructureInfoBox->science[2],SIGNAL(PlaySound(int,int,int)),Sound,SLOT(PlaySystemSound(int,int,int)));
    connect(ConstructureInfoBox->science[3],SIGNAL(PlaySound(int,int,int)),Sound,SLOT(PlaySystemSound(int,int,int)));*/

    connect(Network,SIGNAL(SeEndTurn()),this,SLOT(ReEndTurn()));
    connect(Network,SIGNAL(SeProduce(UnitProduce)),MapWidget,SLOT(ReProduce(UnitProduce)));
    connect(Network,SIGNAL(SeMove(UnitMove)),MapWidget,SLOT(ReMove(UnitMove)));
    connect(Network,SIGNAL(SeFight(UnitFight)),MapWidget,SLOT(ReFight(UnitFight)));
    connect(Network,SIGNAL(SeNewbase(NewBase)),MapWidget,SLOT(ReNewbase(NewBase)));
    connect(Network,SIGNAL(SeNewgame(NewGame)),MapWidget,SLOT(ReNewgame(NewGame)));
    connect(Network,SIGNAL(SeRearch(ResearchFinish)),this,SLOT(ReResearch(ResearchFinish)));
}

void MainWidget::display(area* a)
{
    if(a!=NULL&&a->getUnits()==NULL&&a->getsight()&&(a->oareatype()==GAS||a->oareatype()==CRYSTAL))
    {
        BuildBase->setEnabled(true);
        BuildBase->setVisible(true);
    }
    else
    {
        BuildBase->setEnabled(false);
        BuildBase->setVisible(false);
    }
}


void MainWidget::endturn()
{
    MainGame->endTurn();
    MapWidget->reset();
    MapWidget->EndTurn();
    ResourceInfoBox->repaint();
    if(MainGame->getTurn()==MainGame->getSelf()->getIndex())
        EndTurnButton->setEnabled(true);
    else
        EndTurnButton->setEnabled(false);
    if(MainGame->getMode()==ONLINE)
        Network->sendMessage(ENDTURN);
    refresh();
}

void MainWidget::ReEndTurn()
{
    MainGame->endTurn();
    MapWidget->reset();
    MapWidget->EndTurn();
    ResourceInfoBox->repaint();
    if(MainGame->getTurn()==MainGame->getSelf()->getIndex())
        EndTurnButton->setEnabled(true);
    else
        EndTurnButton->setEnabled(false);
}

void MainWidget::refresh()
{
    MapWidget->resetAllSight();
    repaint();
    MapWidget->repaint();
    ResourceInfoBox->repaint();
    ConstructureInfoBox->repaint();
    UnitInfoWidget->repaint();
    if(MainGame->getTurn()==MainGame->getSelf()->getIndex())
        EndTurnButton->setEnabled(true);
    else
        EndTurnButton->setEnabled(false);
}

void MainWidget::clear()
{
    MapWidget->clearMap();
}

area *MainWidget::getBirthPoint()
{
    return MapWidget->getRandomBirthPoint();
}

void MainWidget::Research(int ind)
{
    if(MainGame->getMode()==ONLINE)
    {
        struct ResearchFinish r;
        r.index=ind;
        Network->sendMessage(r);
    }
    //Sound->PlaySystemSound(MainGame->getSelf()->getIndex(),0,5);
    refresh();
}

void MainWidget::ReResearch(struct ResearchFinish r)
{
    MainGame->getEnemy()->researchTech(r.index-1);
}

void MainWidget::BuileFood()
{
    if(MainGame->getSelf()->getMaxFood()<200)
    {
    if(MainGame->getSelf()->getCrystal()>=100)
    {
        MainGame->getSelf()->incCrystal(-100);
        MainGame->getSelf()->incMaxFood(10);
        //Sound->PlaySystemSound(MainGame->getSelf()->getRace(),0,5);
        emit refresh();
    }
    else
    {
       // Sound->PlaySystemSound(MainGame->getSelf()->getRace(),0,0);
    }
    }
}

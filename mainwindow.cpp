#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapwidget.h"
#include <QMessageBox>

extern Game *MainGame;
extern TcpNet *Network;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //this->setAttribute(Qt::WA_PaintOutsidePaintEvent);
    ui->setupUi(this);
    GameWidget=new MainWidget(this);
    WelWidget=new background(this);
    GameWidget->setEnabled(false);
    GameWidget->setVisible(false);
    WelWidget->setEnabled(true);
    WelWidget->setVisible(true);

    //BGM=new Widget(this);
    //BGM->setVisible(false);
    //BGM->musicon1();

    setGeometry(0,0,WindowWidth,WindowHeight);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags()& ~Qt::WindowCloseButtonHint);
    setFixedSize(this->width(), this->height());

    connect(WelWidget->m_button1,SIGNAL(clicked()),this,SLOT(SingleGame()));
    connect(WelWidget->m_button2,SIGNAL(clicked()),this,SLOT(MultiGame()));
    connect(WelWidget->m_button3,SIGNAL(clicked()),this,SLOT(close()));
    connect(GameWidget->GgButton,SIGNAL(clicked()),this,SLOT(GameOver()));

    connect(Network,SIGNAL(SeNewgame(NewGame)),this,SLOT(ReMultiGame(NewGame)));
    connect(Network,SIGNAL(SeGameOver(int)),this,SLOT(ReGameOver(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SingleGame()
{
    int race;
    if(WelWidget->radio1->isChecked())
        race=PROTOSS;
    if(WelWidget->radio2->isChecked())
        race=TERRAN;
    if(WelWidget->radio3->isChecked())
        race=ZERG;
    if(race==ZERG)
        return;
    if(MainGame!=NULL)
    {
        delete MainGame;
        MainGame=new Game(race);
    }
    area *t;
    GameWidget->clear();
    t=GameWidget->getBirthPoint();
    MainGame->getSelf()->CreatUnit(t,-1,1);
    t=GameWidget->getBirthPoint();
    MainGame->getEnemy()->CreatUnit(t,-1,1);
    WelWidget->setEnabled(false);
    WelWidget->setVisible(false);
    GameWidget->setEnabled(true);
    GameWidget->setVisible(true);
    GameWidget->refresh();
}

void MainWindow::MultiGame()
{
    int race;
    if(Network->netStatus)
    {
    if(WelWidget->radio1->isChecked())
        race=PROTOSS;
    if(WelWidget->radio2->isChecked())
        race=TERRAN;
    if(WelWidget->radio3->isChecked())
        race=ZERG;
    if(race==ZERG)
        return;
    if(MainGame!=NULL)
    {
        delete MainGame;
    }
    struct NewGame ng;
    ng.selfindex=0;
    ng.selfrace=race;
    ng.enemyindex=1;
    ng.enemyrace=1-race;
    ng.turn=0;
    area *t;
    MainGame=new Game(ng);
    GameWidget->clear();
    t=GameWidget->getBirthPoint();
    MainGame->getSelf()->CreatUnit(t,-1,1);
    ng.selfareaindex=t->getindex();
    t=GameWidget->getBirthPoint();
    MainGame->getEnemy()->CreatUnit(t,-1,1);
    ng.enemyareaindex=t->getindex();
    WelWidget->setEnabled(false);
    WelWidget->setVisible(false);
    GameWidget->setEnabled(true);
    GameWidget->setVisible(true);
    GameWidget->refresh();
    Network->sendMessage(ng);
    }
}

void MainWindow::ReMultiGame(struct NewGame ng)
{
    WelWidget->setEnabled(false);
    WelWidget->setVisible(false);
    GameWidget->setEnabled(true);
    GameWidget->setVisible(true);
    GameWidget->refresh();
}

void MainWindow::ReGameOver(int result)
{
    GameWidget->setEnabled(false);
    GameWidget->setVisible(false);
    WelWidget->setEnabled(true);
    WelWidget->setVisible(true);
}

void MainWindow::GameOver()
{
    if(MainGame->getMode()==ONLINE)
        Network->sendMessage(WIN);
    GameWidget->setEnabled(false);
    GameWidget->setVisible(false);
    WelWidget->setEnabled(true);
    WelWidget->setVisible(true);
}

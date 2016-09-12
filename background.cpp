#include "background.h"

#include <QPainter>
#include <QWidget>

extern TcpNet *Network;

background::background(QWidget *parent) :
    QWidget(parent)
{
    QPixmap map1,map2,map3;
    map1.load("./1.jpg");
    map2.load("./2.jpg");
    map3.load("./3.jpg");

    map.load("./abc.jpg");
   // logo.load("./logo.png");
    //map=map.scaled(map.width()*4/6,map.height()*4/6,Qt::KeepAspectRatio);
    map=map.scaled(WindowWidth,WindowHeight,Qt::KeepAspectRatio);
    logo=logo.scaled(logo.width(),logo.height(),Qt::KeepAspectRatio);

    setGeometry(0,0,WindowWidth,WindowHeight);
    m_button1 = new QPushButton(this);
    m_button1->setIconSize(QSize(150,50));
    m_button1-> setIcon(map1);
    // 设置按钮的大小和位置
    m_button1->setGeometry(QRect(QPoint(WindowWidth*14/18, WindowHeight*9/18),
                                 QSize(150, 50)));

    m_button1->setAutoFillBackground(true);
    // 把按钮发出的信号连接到确切的槽
    //connect(m_button, SIGNAL(released()), this, SLOT(handleButton()));


    m_button2 = new QPushButton(this);
    m_button2->setIconSize(QSize(150,50));
    m_button2-> setIcon(map2);
    m_button2->setGeometry(QRect(QPoint(WindowWidth*14/18, WindowHeight*11/18),
                                 QSize(150,50)));
    m_button2->setAutoFillBackground(true);
    //connect(m_button, SIGNAL(released()), this, SLOT(handleButton()));


    m_button3 = new QPushButton(this);
    m_button3->setIconSize(QSize(150,50));
    m_button3-> setIcon(map3);
    m_button3->setGeometry(QRect(QPoint(WindowWidth*14/18, WindowHeight*13/18),
                                 QSize(150,50)));
    m_button3->setAutoFillBackground(true);
    //connect(m_button, SIGNAL(released()), this, SLOT(handleButton()));

    serverIP=new QLabel(this);
    serverIP->setGeometry(WindowWidth*14/18, WindowHeight*1/36,150, 50);
    serverIP->setText(Network->getIPAddress());
    clientIP=new QLineEdit(this);
    clientIP->setGeometry(WindowWidth*14/18, WindowHeight*2/18,150, 30);
    con=new QPushButton(this);
    con->setGeometry(WindowWidth*14/18, WindowHeight*3/18,75, 30);
    con->setText("Connect");
    discon=new QPushButton(this);
    discon->setGeometry(WindowWidth*14/18+80, WindowHeight*3/18,75, 30);
    discon->setText("Disconnect");
    discon->setEnabled(false);

    radioGroup = new QGroupBox("race", this);
    radioGroup->setGeometry(10,10,100,110);
    radio1 = new QRadioButton("Protoss", radioGroup);
    radio1->move(20,35);
    radio1->setChecked(true);
    radio2 = new QRadioButton("Terran", radioGroup);
    radio2->move(20,60);
    radio3 = new QRadioButton("Zerg", radioGroup);
    radio3->move(20,85);

    // init buttons
    //initButtons();

    // signals and slots
    //connect(radio1, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    //connect(radio2, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    //connect(radio3, SIGNAL(clicked(bool)), this, SLOT(radioChange()));

    connect(con,SIGNAL(clicked()),this,SLOT(Con()));
    connect(Network,SIGNAL(SeCon()),this,SLOT(ReCon()));
    connect(discon,SIGNAL(clicked()),this,SLOT(Discon()));
    connect(Network,SIGNAL(SeDiscon()),this,SLOT(ReDiscon()));
}

void background::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawPixmap(0,0,map,0,0,-1,-1);
    p.drawPixmap((WindowWidth-logo.width())/2,-WindowHeight/40,logo,0,0,-1,-1);
}

void background::Con()
{
    Network->newConnect(clientIP->text());
}

void background::Discon()
{
    Network->sendMessage(DISCONNECT);
    Network->close();
    con->setEnabled(true);
    discon->setEnabled(false);
}

void background::ReCon()
{
    con->setEnabled(false);
    discon->setEnabled(true);
}

void background::ReDiscon()
{
    Network->close();
    con->setEnabled(true);
    discon->setEnabled(false);
}

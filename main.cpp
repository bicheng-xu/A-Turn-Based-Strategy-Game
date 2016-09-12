#include "mainwindow.h"
#include <QApplication>
#include "mainwidget.h"
#include "database.h"
#include "tcpnet.h"


//const int MapHeight=2*shortll*15;
//const int MapWidth=3*linelength*11+linelength*2;
DataBase Data;
Game * MainGame;
TcpNet * Network;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Data.unitinit();
    Network=new TcpNet;
    MainWindow w;
    /*MainWidget game(&w);
    background wel(&w);
    game.setEnabled(false);
    game.setVisible(false);
    wel.setEnabled(true);
    wel.setVisible(true);
    */
    w.show();

    return a.exec();
}

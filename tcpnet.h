#ifndef TCPNET_H
#define TCPNET_H

#define CONNECT -1
#define DISCONNECT -2
#define ENDTURN 1
#define PRODUCE 2
#define MOVE 3
#define FIGHT 4
#define NEWBASE 5
#define NEWGAME 6
#define RESEARCH 8
#define WIN 9
#define LOSE 10

#include <QObject>
#include <QtNetwork>
#include "game.h"

struct UnitProduce{
    int areaindex;
    int unitindex;
};

struct UnitMove{
    int areaindex;
    int unitnum;
    int unitindex[6];
    int targetindex;
};

struct UnitFight{
    int areaindex;
    int targetindex;
    int unitnum;
    int unithp[6];
    int unitshield[6];
};

struct NewBase{
    int areaindex;
};

struct NewGame{
    int selfindex;
    int enemyindex;
    int turn;
    int selfareaindex;
    int enemyareaindex;
    int selfrace;
    int enemyrace;
};

struct ResearchFinish{
    int index;
};

class TcpNet : public QObject
{
    Q_OBJECT
public:
    explicit TcpNet(QObject *parent = 0);
    void close();
    //void sendMessage(QString msg);
    void sendMessage(int mag);
    void sendMessage(struct UnitProduce up);
    void sendMessage(struct UnitMove um);
    void sendMessage(struct UnitFight uf);
    void sendMessage(struct NewBase nb);
    void sendMessage(struct NewGame ng);
    void sendMessage(struct ResearchFinish r);
    bool netStatus;

signals:
    void SeEndTurn();
    void SeProduce(struct UnitProduce up);
    void SeMove(struct UnitMove um);
    void SeFight(struct UnitFight uf);
    void SeNewbase(struct NewBase nb);
    void SeNewgame(struct NewGame ng);
    void SeRearch(struct ResearchFinish r);
    void SeCon();
    void SeDiscon();
    void SeGameOver(int result);

private:
    QTcpServer *tcpServer;
    QString message;  //存放从服务器接收到的字符串
    quint16 blockSize;  //存放文件的大小信息
    QTcpSocket *tcpSocket;

public slots:
    //void sendMessage();
    void newConnect(QString ip); //连接服务器
    void readMessage();  //接收数据
    void displayError(QAbstractSocket::SocketError);  //显示错误
    void constructConnection();
    QString getIPAddress();
};

#endif // TCPNET_H

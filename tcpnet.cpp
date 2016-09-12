#include "tcpnet.h"

extern Game *MainGame;
TcpNet::TcpNet(QObject *parent) :
    QObject(parent)
{
    netStatus=false;
    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);
        if(!tcpServer->listen(QHostAddress::Any,6666))
        {  //监听本地主机的6666端口，如果出错就输出错误信息，并关闭
            qDebug() << tcpServer->errorString();
            //newConnect();
        }
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(constructConnection()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
             this,SLOT(displayError(QAbstractSocket::SocketError)));
     //connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
}

/*void TcpNet::sendMessage(QString msg)
{
    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block,QIODevice::WriteOnly);
    //使用数据流写入数据
    out.setVersion(QDataStream::Qt_4_6);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out<<(quint16) 0;
    out<<10000;
    //out<<tr("1");
    //out<<msg;
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    //QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    //我们获取已经建立的连接的子套接字
    //connect(clientConnection,SIGNAL(disconnected()),clientConnection,SLOT(deleteLater()));
    //clientConnection->write(block);
    tcpSocket->write(block);
    //clientConnection->disconnectFromHost();
    //发送数据成功后，显示提示
}*/

QString TcpNet::getIPAddress()
{
QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}

void TcpNet::newConnect(QString ip)
{
    blockSize = 0; //初始化其为0
    tcpSocket->abort(); //取消已有的连接
    tcpSocket->connectToHost(ip,6666);
    //连接到主机，这里从界面获取主机地址和端口号
}

void TcpNet::readMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_6);
    //设置数据流版本，这里要和服务器端相同
    if(blockSize==0) //如果是刚开始接收数据
    {
        //判断接收的数据是否有两字节，也就是文件的大小信息
        //如果有则保存到blockSize变量中，没有则返回，继续接收数据
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> blockSize;
    }
    if(tcpSocket->bytesAvailable() < blockSize) return;
    //如果没有得到全部的数据，则返回，继续接收数据
    int m;
    in>>m;
    switch (m)
    {
    case ENDTURN:
        emit SeEndTurn();
        break;
    case PRODUCE:
        struct UnitProduce up;
        in>>up.areaindex;
        in>>up.unitindex;
        emit SeProduce(up);
        break;
    case MOVE:
        struct UnitMove um;
        in>>um.areaindex;
        in>>um.targetindex;
        in>>um.unitnum;
        for(int i=0;i<um.unitnum;i++)
            in>>um.unitindex[i];
        emit SeMove(um);
        break;
    case FIGHT:
        struct UnitFight uf;
        in>>uf.areaindex;
        in>>uf.targetindex;
        in>>uf.unitnum;
        for(int i=0;i<uf.unitnum;i++)
        {
            in>>uf.unithp[i];
            in>>uf.unitshield[i];
        }
        emit SeFight(uf);
        break;
    case NEWBASE:
        struct NewBase nb;
        in>>nb.areaindex;
        emit SeNewbase(nb);
        break;
    case NEWGAME:
        struct NewGame ng;
        in>>ng.turn;
        in>>ng.selfindex;
        in>>ng.selfrace;
        in>>ng.selfareaindex;
        in>>ng.enemyindex;
        in>>ng.enemyrace;
        in>>ng.enemyareaindex;
        emit SeNewgame(ng);
        break;
    case RESEARCH:
        struct ResearchFinish r;
        in>>r.index;
        emit SeRearch(r);
        break;
    case CONNECT:
        netStatus=true;
        emit SeCon();
        break;
    case DISCONNECT:
        emit SeDiscon();
        break;
    case WIN:
        emit SeGameOver(WIN);
        break;
    case LOSE:
        emit SeGameOver(LOSE);
        break;
    default:
        break;
    }
    blockSize=0;
}

void TcpNet::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString(); //输出错误信息
}

void TcpNet::constructConnection()
{
    netStatus=true;
    tcpSocket=tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    blockSize=0;
    sendMessage(CONNECT);
    emit SeCon();
}

void TcpNet::sendMessage(int msg)
{
    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block,QIODevice::WriteOnly);
    //使用数据流写入数据
    out.setVersion(QDataStream::Qt_4_6);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out<<(quint16) 0;
    out<<msg;
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    tcpSocket->write(block);
}

void TcpNet::sendMessage(struct UnitProduce up)
{
    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block,QIODevice::WriteOnly);
    //使用数据流写入数据
    out.setVersion(QDataStream::Qt_4_6);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out<<(quint16) 0;
    out<<PRODUCE;
    out<<up.areaindex;
    out<<up.unitindex;
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    tcpSocket->write(block);
}

void TcpNet::sendMessage(struct UnitMove um)
{
    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block,QIODevice::WriteOnly);
    //使用数据流写入数据
    out.setVersion(QDataStream::Qt_4_6);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out<<(quint16) 0;
    out<<MOVE;
    out<<um.areaindex;
    out<<um.targetindex;
    out<<um.unitnum;
    for(int i=0;i<um.unitnum;i++)
        out<<um.unitindex[i];
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    tcpSocket->write(block);
}

void TcpNet::sendMessage(struct UnitFight uf)
{
    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block,QIODevice::WriteOnly);
    //使用数据流写入数据
    out.setVersion(QDataStream::Qt_4_6);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out<<(quint16) 0;
    out<<FIGHT;
    out<<uf.areaindex;
    out<<uf.targetindex;
    out<<uf.unitnum;
    for(int i=0;i<uf.unitnum;i++)
    {
        out<<uf.unithp[i];
        out<<uf.unitshield[i];
    }
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    tcpSocket->write(block);
}

void TcpNet::sendMessage(struct NewBase nb)
{
    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block,QIODevice::WriteOnly);
    //使用数据流写入数据
    out.setVersion(QDataStream::Qt_4_6);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out<<(quint16) 0;
    out<<NEWBASE;
    out<<nb.areaindex;
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    tcpSocket->write(block);
}

void TcpNet::sendMessage(struct NewGame ng)
{
    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block,QIODevice::WriteOnly);
    //使用数据流写入数据
    out.setVersion(QDataStream::Qt_4_6);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out<<(quint16) 0;
    out<<NEWGAME;
    out<<ng.turn;
    out<<ng.selfindex;
    out<<ng.selfrace;
    out<<ng.selfareaindex;
    out<<ng.enemyindex;
    out<<ng.enemyrace;
    out<<ng.enemyareaindex;
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    tcpSocket->write(block);
}

void TcpNet::sendMessage(struct ResearchFinish r)
{
    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block,QIODevice::WriteOnly);
    //使用数据流写入数据
    out.setVersion(QDataStream::Qt_4_6);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out<<(quint16) 0;
    out<<RESEARCH;
    out<<r.index;
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    tcpSocket->write(block);
}

void TcpNet::close()
{
    netStatus=false;
    tcpSocket->disconnectFromHost();
}

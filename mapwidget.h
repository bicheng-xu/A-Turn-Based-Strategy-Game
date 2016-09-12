#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "myframe.h"
#include <QMessageBox>
#include <QPainter>
#include "mapmovewidget.h"
#include <QRect>
#include <fstream>
#include <QEventLoop>
#include <QTimer>
#include <qmath.h>
#include "tcpnet.h"

using namespace std;

const int WindowHeight=708;
const int WindowWidth=1366;
//const int WindowHeight=768;
//const int WindowWidth=1024;
const int RightTabHeight=WindowHeight;
const int RightTabWidth=WindowWidth*0.2;
const int BottomTabHeight=0;
const int BottomTabWidth=WindowWidth-RightTabWidth;
const int MapHeight=WindowHeight-BottomTabHeight;
const int MapWidth=WindowWidth-RightTabWidth;
const int PadWidth=10;

//vector<area> MapVect;
//int NumofRow=0;
//int NumofCol=0;
//int currentRow=0,currentCol=0;

//myframe *current=NULL;

class mapwidget : public QWidget
{
    Q_OBJECT
private:
    qreal MapX;
    qreal MapY;
    qreal times;
    qreal MapHeight;
    qreal MapWidth;
    QPixmap Map;
    vector<area> MapVect;
    myframe *current;
    area * selected;
    bool MoveFlag;
public:
    explicit mapwidget(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    QPixmap getMap();
    void setReachable();
    bool setSight(area* ar);
    void cancelSight(area* ar);
    void resetAllSight();
    void setAttack();
    void fight(UnitGroup *UnitShellfir,UnitGroup *UnitShellsec);
    void reset();
    void clearMap();
    area *getRandomBirthPoint();
    void EndTurn();

signals:
    void MapMoving(int dir);
    void UnitSelected(area* a);
    void refresh();
    void PlaySound(int Race,int Index,int Type);

public slots:
    void MapMoved(int dir);
    void FocusChanged(myframe *ptr);
    void SelectUnit(area* a,int cl);
    void ReProduce(struct UnitProduce up);
    void ReMove(struct UnitMove um);
    void ReFight(struct UnitFight uf);
    void ReNewbase(struct NewBase nb);
    void ReNewgame(struct NewGame ng);
    void ProduceUnit(int ind);
    void BuildNewBase();
};

#endif // MAPWIDGET_H

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "myframe.h"
#include <QPainter>
#include <QObject>
#include "mapwidget.h"
#include "mapmovewidget.h"
#include "area.h"
#include <vector>
#include <QSlider>
#include <QLCDNumber>
#include <QLabel>
#include <QTextCodec>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include "unitinfbox.h"
#include "game.h"
#include "crystalgasfood.h"
#include "structureinfbox.h"
#include "endturn.h"
#include "tcpnet.h"

class Unitinfbox;
class crystalgasfood;
class structureinfbox;
class ggButton;
class MainWidget : public QWidget
{
    Q_OBJECT
private:
    mapwidget * MapWidget;
    Unitinfbox *UnitInfoWidget;
    crystalgasfood *ResourceInfoBox;
    structureinfbox *ConstructureInfoBox;
    class endturn *EndTurnButton;
    QPushButton *BuildBase;

    //area *selectedarea;

public:
    explicit MainWidget(QWidget *parent = 0);
    void clear();
    area *getBirthPoint();
    QPushButton *GgButton;

signals:

public slots:
    void display(area* a);
    void endturn();
    void ReEndTurn();
    void ReResearch(struct ResearchFinish r);
    void refresh();
    void Research(int ind);
    void BuileFood();
};

#endif // MAINWIDGET_H

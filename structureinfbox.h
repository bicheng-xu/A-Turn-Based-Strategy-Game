#ifndef STRUCTUREINFBOX_H
#define STRUCTUREINFBOX_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QString>
#include "mainwindow.h"
#include "produceunitwidget.h"
#include "sciencewidget.h"
#include "mapwidget.h"
#include "foodadd.h"

class sciencewidget;
class structureinfbox : public QWidget
{
    Q_OBJECT
private:
    QLabel *shield;
    QLabel *def;
    QLabel *healthc;
    QLabel *shieldc;
    QLabel *defc;
    QLabel *produceq;
    QLabel *sciencet;
    QLabel *status;
    QLabel *health;
    QLabel *name;
    QLabel *workernumber;
    QLabel *crystalnumber;
    QLabel *gasnumber;

    int WorkerOnCrystal;
    int WorkerOnGas;

    QPixmap map;

    QProgressBar *pbar[3];

    produceunitwidget *produce[4][4];

    foodadd *foodadd1;

    area* str;
public:
    explicit structureinfbox(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    sciencewidget *science[4];
signals:
    void Research(int ind);
    void Produce(int ind);
    void AddFood();
public slots:
    void restructureinf(area* stru);
    void clickResearch(int ind);
    void clickProduce(int ind);
    void clickAddFood();
};

#endif // STRUCTUREINFBOX_H

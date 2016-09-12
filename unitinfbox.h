#ifndef UNITINFBOX_H
#define UNITINFBOX_H

#include <QLabel>
#include <QPainter>
#include <QWidget>
#include <QString>
#include <QProgressBar>
#include <QPushButton>
#include "mainwindow.h"
#include "mapwidget.h"
#include "unitbar.h"

class unitbar;
class Unitinfbox : public QWidget
{
    Q_OBJECT
private:
    QLabel *crystal;
    QLabel *gas;
    QLabel *food;

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
    QLabel *skills;

    QLabel *queuelabel;

    QLabel *UnitLabel[6];

    QProgressBar *progressbar[6];
    QProgressBar *progressbar1[6][2];
    QProgressBar *progressbar2[6][3];

    int selectstatus[6];
    area* arar;

    unitbar *unitbarshell[6];
public:
    explicit Unitinfbox(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    //area* temparea;
    void mousePressEvent(QMouseEvent *);
signals:
    void cl(int i);
public slots:
    void re(area* j);
};

#endif // UNITINFBOX_H

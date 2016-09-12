#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <math.h>
#include <QMouseEvent>
#include "area.h"

#define FOCUSON 1

const qreal linelength=40;
const qreal shortll=sqrt(3)*linelength/2;

class myframe : public QFrame
{
    Q_OBJECT
private:
    QPixmap unit_table;
    QPixmap P_Base;
    QPixmap T_Base;
    int state;
    qreal times;
public:
    explicit myframe(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *event);
    void moveon();
    void setstate(int s);
    int getstate(int s);
    area * ptrToArea;
signals:
    void MouseMoveon(myframe *ptr);
    void SelectaUnit(area* a,int cl);
public slots:
    void MapMoved(int dir);
};

#endif // MYFRAME_H

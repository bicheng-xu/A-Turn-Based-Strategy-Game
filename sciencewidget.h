#ifndef SCIENCEWIDGET_H
#define SCIENCEWIDGET_H

#include <QWidget>
#include <QPainter>
#include "game.h"
#include "mainwidget.h"

class sciencewidget : public QWidget
{
    Q_OBJECT
private:
    int race;
    int index;
    int setornot;
public:
    explicit sciencewidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void inputraceindex(int i, int j);
signals:
    void sciencesig(int i);
    void PlaySound(int Race,int Index,int Type);
};

#endif // SCIENCEWIDGET_H

#ifndef MAPMOVEWIDGET_H
#define MAPMOVEWIDGET_H

#define TOP 1
#define BOTTOM 2
#define LEFT 3
#define RIGHT 4


#include <QWidget>

class MapMoveWidget : public QWidget
{
    Q_OBJECT
private:
    int direction;
public:
    explicit MapMoveWidget(QWidget *parent = 0, int dir=0);
    void mouseMoveEvent(QMouseEvent *);


signals:
    void MoveMap(int dir);

public slots:

};

#endif // MAPMOVEWIDGET_H

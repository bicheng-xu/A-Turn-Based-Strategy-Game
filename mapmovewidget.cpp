#include "mapmovewidget.h"

MapMoveWidget::MapMoveWidget(QWidget *parent,int dir) :
    QWidget(parent)
{
    direction=dir;
    setMouseTracking(true);
}

void MapMoveWidget::mouseMoveEvent(QMouseEvent *)
{
    emit MoveMap(direction);
}

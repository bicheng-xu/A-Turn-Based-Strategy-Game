#ifndef ENDTURN_H
#define ENDTURN_H

#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"
#include "mapwidget.h"

class endturn : public QWidget
{
    Q_OBJECT
private:
    QPushButton *endturnb;
public:
    explicit endturn(QWidget *parent = 0);
signals:
    void seendturn();
public slots:
    void reendturn();
};

#endif // ENDTURN_H

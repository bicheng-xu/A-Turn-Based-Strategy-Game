#ifndef GGBUTTON_H
#define GGBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"
#include "mapwidget.h"

class ggButton : public QWidget
{
    Q_OBJECT
public:
    explicit ggButton(QWidget *parent = 0);
    QPushButton *ggbutton;
signals:
    void segg();
public slots:
    void regg();
};

#endif // GGBUTTON_H

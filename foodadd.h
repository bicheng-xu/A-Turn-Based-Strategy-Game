#ifndef FOODADD_H
#define FOODADD_H

#include <QWidget>
#include <QPainter>

class foodadd : public QWidget
{
    Q_OBJECT
private:
    int race;
public:
    explicit foodadd(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void inputrace(int a);
signals:
    void foodsig();
public slots:

};

#endif // FOODADD_H

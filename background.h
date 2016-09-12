#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include "mainwindow.h"
#include "mapwidget.h"
#include "tcpnet.h"

class background : public QWidget
{
    Q_OBJECT
public:
    explicit background(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void initButtons();
    QPushButton *m_button1;
    QPushButton *m_button2;
    QPushButton *m_button3;
    QGroupBox *radioGroup;
    QRadioButton *radio1;
    QRadioButton *radio2;
    QRadioButton *radio3;
    QLabel *label11;
    QLabel *label12;
    QLabel *label13;
    QPixmap map;
    QPixmap logo;
    QLineEdit *clientIP;
    QPushButton *con;
    QPushButton *discon;
    QLabel *serverIP;
signals:
    
public slots:
    void Con();
    void Discon();
    void ReCon();
    void ReDiscon();
};

#endif // BACKGROUND_H


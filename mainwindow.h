#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "background.h"
#include "mainwidget.h"

namespace Ui {
class MainWindow;
}

class MainWidget;
class background;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainWidget *GameWidget;
    background *WelWidget;

public slots:
    void SingleGame();
    void MultiGame();
    void ReMultiGame(struct NewGame ng);
    void ReGameOver(int result);
    void GameOver();
};

#endif // MAINWINDOW_H

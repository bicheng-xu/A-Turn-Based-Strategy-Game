#include "game.h"

Game::Game()
{
    Self=new Player(0,TERRAN);
    Enemy=new Player(1,PROTOSS);
    Turn=0;
    Mode=OFFLINE;
}

Game::Game(int race)
{
    Self=new Player(0,race);
    Enemy=new Player(1,1-race);
    Turn=0;
    Mode=OFFLINE;
}

Game::Game(struct NewGame ng)
{
    Self=new Player(ng.selfindex,ng.selfrace);
    Enemy=new Player(ng.enemyindex,ng.enemyrace);
    Turn=ng.turn;
    Mode=ONLINE;
}

Player * Game::getSelf()
{
    return Self;
}

Player * Game::getEnemy()
{
    return Enemy;
}

void Game::endTurn()
{
    Turn=1-Turn;
    if(Mode==OFFLINE)
    {
        Player *tmp=Self;
        Self=Enemy;
        Enemy=tmp;
        Self->reset();
    }
    if(Mode==ONLINE)
    {

    }
}

int Game::getTurn()
{
    return Turn;
}

int Game::getMode()
{
    return Mode;
}

void Game::setMode(int m)
{
    Mode=m;
}

#ifndef GAME_H
#define GAME_H

#define ONLINE 2
#define OFFLINE 1

#include "player.h"
#include "tcpnet.h"

class Player;
class Game
{
private:
    int Turn;
    Player *Self;
    Player *Enemy;
    int Mode;

public:
    Game();
    Game(int race);
    Game(struct NewGame ng);
    Player * getSelf();
    Player * getEnemy();
    int getTurn();
    void endTurn();
    int getMode();
    void setMode(int m);
};

#endif // GAME_H

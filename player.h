#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "unit.h"
#include "area.h"
#include <vector>
#include "unitgroup.h"
#include "database.h"

class area;

struct technode{
    int status;
    int CrystalCost;
    int GasCost;
    struct technode* basetech;
};

class Player
{
private:
    int Index;
    std::string Name;
    int Race;
    int Crystal;
    int Gas;
    int CurrentFood;
    int MaxFood;
    technode *techtree[4];
    //std::vector<UnitGroup> Units;
public:
    Player();
    Player(int ind,int r);
    int getIndex();
    int getRace();
    int getCrystal();
    int getGas();
    int getMaxFood();
    int getCurrentFood();
    void CreatUnit(area *ar,int index,int num);
    void reset();
    bool getTechStatus(int id);
    bool checkTechBase(int id);
    void researchTech(int id);
    int getTechCrystalCost(int id);
    int getTechGasCost(int id);
    void incCrystal(int c);
    void incGas(int g);
    void incCurrentFood(int cf);
    void incMaxFood(int mf);
    bool checkUnitTech(int ind);
};

#endif // PLAYER_H

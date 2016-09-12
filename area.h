#ifndef AREA_H
#define AREA_H

#include <string>
#include "unitgroup.h"
#include "game.h"

using std::string;

//Reachornot
#define REACH_ABLE 0
#define REACH_UNABLE 1

//Areatype
#define UNDEFINE -1
#define GROUND 0
#define BRAE 1
#define GRASS 2
#define LOOKOUT_TOWER 3
#define INSKY 4
#define CRYSTAL 5
#define GAS 6

#define TOPTOP 0
#define TOPRIGHT 1
#define BOTTOMRIGHT 2
#define BOTTOMBOTTOM 3
#define BOTTOMLEFT 4
#define TOPLEFT 5

class area{
private:
    int x;
    int y;

    int index;
    int areatype;
    int reachornot;
    int state;
    int sight;
    int distance;
    int attackable;

    int *unitpoint;

    int unitnumber;

    int height;

    area * Link[6];

    bool flag;

    bool selected;

    string cospicturepath;

    UnitGroup *units;
    std::vector<UnitGroup> a;
    area * LastStep;
public:
    area();
    void ix(int a);
    int ox();
    void iy(int a);
    int oy();
    void iareatype(int a);
    int oareatype();
    void ireachornot(int a);
    int oreachornot();
    void iunitpoint(int *a);
    int* ounitpoint();
    void iunitnumber(int a);
    int ounitnumber();
    void iheight(int a);
    int oheight();
    void icospicturepath(string a);
    void setLink(int dir, area *iter);
    area * getLink(int dir);
    int getstate();
    bool getflag();
    void setflag(bool f);
    void select();
    void unselect();
    bool ifselected();
    string ocospicturepath();
    UnitGroup *getUnits();
    void setUnits(UnitGroup* u);
    void setLastStep(area* ls);
    area * getLastStep();
    void resetsight();
    void decsight();
    bool incsight();
    int getsight();
    void setdistance(int dis);
    int getdistance();
    void setattackable(int atk);
    int getattackable();
    void setindex(int ind);
    int getindex();
};

#endif // AREA_H

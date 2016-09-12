#ifndef UNIT_H
#define UNIT_H

#include <string>

using std::string;

//For race
#define NOTHING -1
#define PROTOSS 0
#define TERRAN 1
#define ZERG 2
#define OBSTACLE 3

#define SIGHTRANGE 6
#define LOOKTOWERSIGHT 10

//For battle type
#define BATTLE_TYPE_LAND 0
#define BATTLE_TYPE_AIR 1

//For str type
#define UNABLE 0
#define NORMAL_TYPE 1
#define PUNCTURE_TYPE 2
#define EXPLODE_TYPE 3

//For def type
#define LIGHTARMOUR 0
#define HEAVYARMOUR 0

//For visibility type
#define VISIBLE 0
#define UNVISIBLE 1

const double unitX=10,unitY=10,lightGap=400,pixWidth=80,pixHeight=80,blank=25,raceGap=287.5;

class unit{
private:
    string name;

    int master;
    int race;

    int index;

    int battletype;

    int healthmax;
    int healthcurrent;

    int airstr;
    int airstrtype;
    double airstrspeed;
    int airstrrage;

    int landstr;
    int landstrtype;
    double landstrspeed;
    int landstrrage;

    int def;
    int deftype;

    int shieldmax;
    int shielddef;
    int shieldcurrent;

    int manamax;
    int manacurrent;

    int movespeed;

    int visibility;

    int popularity;

    int crystalcost;
    int gascost;

    int selected;

    int workplace;
public:
    unit();
    void iname(string a);
    string oname();
    void irace(int a);
    int orace();
    void iindex(int a);
    int oindex();
    void ibattletype(int a);
    int obattletype();
    void ihealthmax(int a);
    int ohealthmax();
    void ihealthcurrent(int a);
    int ohealthcurrent();
    void iairstr(int a);
    int oairstr();
    void iairstrtype(int a);
    int oairstrtype();
    void iairstrspeed(double a);
    double oairstrspeed();
    void iairstrrage(int a);
    int oairstrrage();
    void ilandstr(int a);
    int olandstr();
    void ilandstrtype(int a);
    int olandstrtype();
    void ilandstrspeed(double a);
    double olandstrspeed();
    void ilandstrrage(int a);
    int olandstrrage();
    void idef(int a);
    int odef();
    void ideftype(int a);
    int odeftype();
    void ishieldmax(int a);
    int oshieldmax();
    void ishielddef(int a);
    int oshielddef();
    void ishieldcurrent(int a);
    int oshieldcurrent();
    void imanamax(int a);
    int omanamax();
    void imanacurrent(int a);
    int omanacurrent();
    void imovespeed(int a);
    int omovespeed();
    void ivisibility(int a);
    int ovisibility();
    void imaster(int ma);
    int omaster();
    void ipopularity(int p);
    int opopularity();
    void icrystalcost(int c);
    int ocrystalcost();
    void igascost(int g);
    int ogascost();
    double getPixX();
    double getPixY();
    void setselected(int s);
    int getselected();
    void setworkplace(int wp);
    int getworkplace();
};


#endif // UNIT_H

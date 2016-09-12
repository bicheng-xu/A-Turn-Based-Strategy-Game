#include "area.h"

extern Game * MainGame;
//Basic member function for class area
area::area()
{
    areatype=UNDEFINE;
    height=0;
    flag=false;
    selected=0;
    reachornot=0;
    LastStep=NULL;
    sight=0;
    distance=0;
    attackable=0;
    for(int i=0;i<6;i++)
        Link[i]=NULL;
    units=NULL;
}

void area::ix(int a){
    x=a;
}
int area::ox(){
    return x;
}
void area::iy(int a){
    y=a;
}
int area::oy(){
    return y;
}
void area::iareatype(int a){
    areatype=a;
}
int area::oareatype(){
    return areatype;
}
void area::ireachornot(int a){
    reachornot=a;
}
int area::oreachornot(){
    return reachornot;
}
void area::iunitpoint(int *a){
    unitpoint=a;
}
int* area::ounitpoint(){
    return unitpoint;
}
void area::iunitnumber(int a){
    unitnumber=a;
}
int area::ounitnumber(){
    return unitnumber;
}
void area::iheight(int a){
    height=a;
}
int area::oheight(){
    return height;
}
void area::icospicturepath(string a){
    cospicturepath=a;
}
string area::ocospicturepath(){
    return cospicturepath;
}

void area::setLink(int dir,area * iter)
{
    Link[dir]=iter;
}

area * area::getLink(int dir)
{
    return Link[dir];
}

int area::getstate()
{
    return state;
}

bool area::getflag()
{
    return flag;
}

void area::setflag(bool f)
{
    flag=f;
}

void area::select()
{
    selected=true;
}

void area::unselect()
{
    selected=false;
}

bool area::ifselected()
{
    return selected;
}

UnitGroup * area::getUnits()
{
    return units;
}

void area::setUnits(UnitGroup* u)
{
    units=u;
}

void area::setLastStep(area* ls)
{
    LastStep=ls;
}

area * area::getLastStep()
{
   return LastStep;
}

void area::resetsight()
{
    sight=0;
}

void area::decsight()
{
    if (sight)
        sight--;
}

bool area::incsight()
{
    bool flag=false;
    if(!sight)
    {
        if(units!=NULL&&units->getUnitInfo().omaster()!=MainGame->getSelf()->getIndex())
            flag=true;
    }
    sight++;
    return flag;
}


void area::setdistance(int dis)
{
    distance=dis;
}

int area::getdistance()
{
    return distance;
}

int area::getsight()
{
    return sight;
}

void area::setattackable(int atk)
{
    attackable=atk;
}

int area::getattackable()
{
    return attackable;
}

void area::setindex(int ind)
{
    index=ind;
}

int area::getindex()
{
    return index;
}

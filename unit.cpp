#include "unit.h"

//Basic I/O member function
unit::unit()
{
    selected=1;
}

void unit::iname(string a){
    name=a;
}
string unit::oname(){
    return name;
}
void unit::irace(int a){
    race=a;
}
int unit::orace(){
    return race;
}
void unit::iindex(int a){
    index=a;
}
int unit::oindex(){
    return index;
}
void unit::ibattletype(int a){
    battletype=a;
}
int unit::obattletype(){
    return battletype;
}
void unit::ihealthmax(int a){
    healthmax=a;
}
int unit::ohealthmax(){
    return healthmax;
}
void unit::ihealthcurrent(int a){
    healthcurrent=a;
}
int unit::ohealthcurrent(){
    return healthcurrent;
}
void unit::iairstr(int a){
    airstr=a;
}
int unit::oairstr(){
    return airstr;
}
void unit::iairstrtype(int a){
    airstrtype=a;
}
int unit::oairstrtype(){
    return airstrtype;
}
void unit::iairstrspeed(double a){
    airstrspeed=a;
}
double unit::oairstrspeed(){
    return airstrspeed;
}
void unit::iairstrrage(int a){
    airstrrage=a;
}
int unit::oairstrrage(){
    return airstrrage;
}
void unit::ilandstr(int a){
    landstr=a;
}
int unit::olandstr(){
    return landstr;
}
void unit::ilandstrtype(int a){
    landstrtype=a;
}
int unit::olandstrtype(){
    return landstrtype;
}
void unit::ilandstrspeed(double a){
    landstrspeed=a;
}
double unit::olandstrspeed(){
    return landstrspeed;
}
void unit::ilandstrrage(int a){
    landstrrage=a;
}
int unit::olandstrrage(){
    return landstrrage;
}
void unit::idef(int a){
    def=a;
}
int unit::odef(){
    return def;
}
void unit::ideftype(int a){
    deftype=a;
}
int unit::odeftype(){
    return deftype;
}
void unit::ishieldmax(int a){
    shieldmax=a;
}
int unit::oshieldmax(){
    return shieldmax;
}
void unit::ishielddef(int a){
    shielddef=a;
}
int unit::oshielddef(){
    return shielddef;
}
void unit::ishieldcurrent(int a){
    shieldcurrent=a;
}
int unit::oshieldcurrent(){
    return shieldcurrent;
}
void unit::imanamax(int a){
    manamax=a;
}
int unit::omanamax(){
    return manamax;
}
void unit::imanacurrent(int a){
    manacurrent=a;
}
int unit::omanacurrent(){
    return manacurrent;
}
void unit::imovespeed(int a){
    movespeed=a;
}
int unit::omovespeed(){
    return movespeed;
}
void unit::ivisibility(int a){
    visibility=a;
}
int unit::ovisibility(){
    return visibility;
}

double unit::getPixX()
{
   int tmp;
   tmp=(index-1)%5;
   return tmp*pixWidth;
}

double unit::getPixY()
{
   int tmp;
   tmp=(index-1)/5;
   return race*raceGap+tmp*pixHeight+blank;
}

void unit::imaster(int ma)
{
    master=ma;
}

int unit::omaster()
{
    return master;
}

void unit::setselected(int s)
{
    selected=s;
}

int unit::getselected()
{
    return selected;
}

void unit::ipopularity(int p)
{
    popularity=p;
}

int unit::opopularity()
{
    return popularity;
}

void unit::icrystalcost(int c)
{
    crystalcost=c;
}

int unit::ocrystalcost()
{
    return crystalcost;
}

void unit::igascost(int g)
{
    gascost=g;
}

int unit::ogascost()
{
    return gascost;
}

void unit::setworkplace(int wp)
{
    workplace=wp;
}

int unit::getworkplace()
{
    return workplace;
}

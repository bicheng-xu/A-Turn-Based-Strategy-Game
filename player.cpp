#include "player.h"

extern DataBase Data;
Player::Player()
{
    Gas=0;
    Crystal=0;
    MaxFood=10;
    CurrentFood=0;
}

Player::Player(int ind,int r)
{
    Index=ind;
    Race=r;
    Gas=0;
    Crystal=1000;
    MaxFood=10;
    CurrentFood=0;
    if(r==PROTOSS)
    {
        for(int i=0;i<3;i++)
            techtree[i]=new struct technode;
        techtree[0]->CrystalCost=150;
        techtree[0]->GasCost=0;
        techtree[0]->status=0;
        techtree[0]->basetech=NULL;
        techtree[1]->CrystalCost=150;
        techtree[1]->GasCost=0;
        techtree[1]->status=0;
        techtree[1]->basetech=techtree[0];
        techtree[2]->CrystalCost=200;
        techtree[2]->GasCost=100;
        techtree[2]->status=0;
        techtree[2]->basetech=techtree[1];
    }
    techtree[3]=new struct technode;
    techtree[3]->status=-1;
    if(r==TERRAN)
    {
        for(int i=0;i<=3;i++)
            techtree[i]=new struct technode;
        techtree[0]->CrystalCost=150;
        techtree[0]->GasCost=0;
        techtree[0]->status=0;
        techtree[0]->basetech=NULL;
        techtree[1]->CrystalCost=50;
        techtree[1]->GasCost=25;
        techtree[1]->status=0;
        techtree[1]->basetech=techtree[0];
        techtree[2]->CrystalCost=150;
        techtree[2]->GasCost=100;
        techtree[2]->status=0;
        techtree[2]->basetech=techtree[0];
        techtree[3]->CrystalCost=50;
        techtree[3]->GasCost=25;
        techtree[3]->status=0;
        techtree[3]->basetech=techtree[2];
    }
}

void Player::CreatUnit(area *ar,int index,int num)
{
   unit newUnit;
   if(index!=1&&index!=16)
    newUnit=Data.getUnit(Race,index);
   else
   {
       newUnit=Data.getUnit(Race,1);
       if(index==1)
            newUnit.setworkplace(CRYSTAL);
       else
            newUnit.setworkplace(GAS);
   }
   newUnit.imaster(Index);
   UnitGroup *UnitShell=ar->getUnits();
   if(UnitShell!=NULL)
   {
       UnitShell->setMovePoint(-1);
       for(int i=0;i<num;i++)
       {
           UnitShell->incUnitNum();
           UnitShell->getUnitShell()->push_back(newUnit);
       }
   }
   else
   {
       UnitGroup *tmpug=new UnitGroup;
       tmpug->setMovePoint(-1);
       std::vector<unit> *tmpus;
       tmpus=tmpug->getUnitShell();
       for(int i=0;i<num;i++)
       {
           tmpug->incUnitNum();
           tmpus->push_back(newUnit);
       }
       ar->setUnits(tmpug);
   }
}

int Player::getIndex()
{
    return Index;
}

int Player::getRace()
{
    return Race;
}

int Player::getCrystal()
{
    return Crystal;
}

int Player::getGas()
{
    return Gas;
}

int Player::getMaxFood()
{
    return MaxFood;
}

int Player::getCurrentFood()
{
    return CurrentFood;
}

void Player::reset()
{
    /*for(std::vector<UnitGroup>::iterator iter=Units.begin();iter<Units.end();iter++)
    {
        if((iter)->getUnitNum()==0||(iter)->getUnitShell()==NULL)
        {
            Units.erase(iter);
            iter--;
        }
        else
        {
            if((iter)->getUnitInfo().oindex()==-1)
            {
            }
            else
            {
                (iter)->setMovePoint((iter)->getUnitInfo().omovespeed());
            }
        }
    }*/
}

bool Player::checkTechBase(int id)
{
    if(techtree[id]->status<0)
        return false;
    if(techtree[id]->basetech==NULL||techtree[id]->basetech->status)
        return true;
    else
        return false;
}

void Player::researchTech(int id)
{
    techtree[id]->status=1;
}

int Player::getTechCrystalCost(int id)
{
    return techtree[id]->CrystalCost;
}

int Player::getTechGasCost(int id)
{
    return techtree[id]->GasCost;
}

void Player::incCrystal(int c)
{
    Crystal+=c;
}

void Player::incGas(int g)
{
    Gas+=g;
}

void Player::incCurrentFood(int cf)
{
    CurrentFood+=cf;
}

void Player::incMaxFood(int mf)
{
    MaxFood+=mf;
}

bool Player::getTechStatus(int id)
{
    if(techtree[id]->status<0)
        return false;
    if(techtree[id]->status)
        return true;
    else
        return false;
}

bool Player::checkUnitTech(int ind)
{
    if(Race==PROTOSS)
    {
        switch(ind)
        {
        case 2:
            if(techtree[0]->status)
                return true;
            else
                return false;
        case 3:
        case 4:
            if(techtree[1]->status)
                return true;
            else
                return false;
        case 6:
        case 8:
            if(techtree[2]->status)
                return true;
            else
                return false;
        default:
            return true;
        }
    }
    if(Race==TERRAN)
    {
        switch(ind)
        {
        case 2:
        case 4:
            if(techtree[0]->status)
                return true;
            else
                return false;
        case 3:
        case 5:
            if(techtree[1]->status)
                return true;
            else
                return false;
        case 6:
            if(techtree[2]->status)
                return true;
            else
                return false;
        case 7:
        case 8:
            if(techtree[3]->status)
                return true;
            else
                return false;
        default:
            return true;
        }
    }
}

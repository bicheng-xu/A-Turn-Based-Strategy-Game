#include "unitgroup.h"

UnitGroup::UnitGroup()
{
    UnitNum=0;
}

std::vector<unit> * UnitGroup::getUnitShell()
{
    return &UnitShell;
}

int UnitGroup::getUnitNum()
{
   return UnitNum;
}

void UnitGroup::incUnitNum()
{
    UnitNum++;
}

void UnitGroup::decUnitNum()
{
    if (UnitNum)
    {
        UnitNum--;
    }
}

unit UnitGroup::getUnitInfo()
{
    return *UnitShell.begin();
}

void UnitGroup::setMovePoint(int mp)
{
    MovePoint=mp;
}

int UnitGroup::getMovePoint()
{
    return MovePoint;
}

void UnitGroup::setUnitNum(int num)
{
    UnitNum=num;
}

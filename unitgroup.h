#ifndef UNITGROUP_H
#define UNITGROUP_H

#include <vector>
#include "unit.h"

class UnitGroup
{
private:
    int UnitNum;
    int MovePoint;
    std::vector<unit> UnitShell;
public:
    UnitGroup();
    std::vector<unit> * getUnitShell();
    unit getUnitInfo();
    int getUnitNum();
    void decUnitNum();
    void incUnitNum();
    void setUnitNum(int num);
    void setMovePoint(int mp);
    int getMovePoint();
};

#endif // UNITGROUP_H

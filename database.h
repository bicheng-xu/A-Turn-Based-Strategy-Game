#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "unit.h"
#include <fstream>
#include <string>

class DataBase
{
private:
     std::vector<unit> Terran;
     std::vector<unit> Protoss;
     std::vector<unit> Zerg;
public:
    DataBase();
    void unitinit();
    unit getUnit(int race,int index);
};

#endif // DATABASE_H

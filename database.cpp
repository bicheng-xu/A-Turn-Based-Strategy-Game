#include "database.h"

DataBase::DataBase()
{
}

void DataBase::unitinit()
{
    std::fstream infile;
    infile.open("unit.dat",std::ios::in);

    unit tempunit;
    int tempint;
    double tempdouble;
    string tempstring;

/*	if (!infile){
        cout << "Read unit information error." << endl;
        return -1;
    }*/

    while (!infile.eof())
    {

        infile >> tempstring;
        tempunit.iname(tempstring);

        infile >> tempint;
        tempunit.irace(tempint);

        infile >> tempint;
        tempunit.iindex(tempint);

        infile >> tempint;
        tempunit.ibattletype(tempint);

        infile >> tempint;
        tempunit.ihealthmax(tempint);
        infile >> tempint;
        tempunit.ihealthcurrent(tempint);

        infile >> tempint;
        tempunit.iairstr(tempint);
        infile >> tempint;
        tempunit.iairstrtype(tempint);
        infile >> tempdouble;
        tempunit.iairstrspeed(tempdouble);
        infile >> tempint;
        tempunit.iairstrrage(tempint);

        infile >> tempint;
        tempunit.ilandstr(tempint);
        infile >> tempint;
        tempunit.ilandstrtype(tempint);
        infile >> tempdouble;
        tempunit.ilandstrspeed(tempdouble);
        infile >> tempint;
        tempunit.ilandstrrage(tempint);

        infile >> tempint;
        tempunit.idef(tempint);
        infile >> tempint;
        tempunit.ideftype(tempint);

        infile >> tempint;
        tempunit.ishieldmax(tempint);
        infile >> tempint;
        tempunit.ishielddef(tempint);
        infile >> tempint;
        tempunit.ishieldcurrent(tempint);

        infile >> tempint;
        tempunit.imanamax(tempint);
        infile >> tempint;
        tempunit.imanacurrent(tempint);

        infile >> tempint;
        tempunit.imovespeed(tempint);

        infile >> tempint;
        tempunit.ivisibility(tempint);

        infile>> tempint;
        tempunit.ipopularity(tempint);

        infile>> tempint;
        tempunit.icrystalcost(tempint);

        infile>> tempint;
        tempunit.igascost(tempint);

        switch(tempunit.orace())
        {
        case PROTOSS:
            Protoss.push_back(tempunit);
            break;
        case TERRAN:
            Terran.push_back(tempunit);
            break;
        case ZERG:
            Zerg.push_back(tempunit);
            break;
        default:
            break;
        }
    }

    infile.close();
    //infile.clear();

    return;
}

unit DataBase::getUnit(int race,int index)
{
    std::vector<unit>::iterator iter;
    unit t;
    t.iindex(-1111);
    switch(race)
    {
    case PROTOSS:
        iter=Protoss.begin();
        while(iter->oindex()!=index)
        {
            iter++;
            if(iter>=Protoss.end())
                return t;
        }
        if(iter->orace()==PROTOSS)
            return *iter;
        else
            return t;
        //return *(Protoss.begin()+index-1);
    case TERRAN:
        iter=Terran.begin();
        while(iter->oindex()!=index)
        {
            iter++;
            if(iter>=Terran.end())
                return t;
        }
        if(iter->orace()==TERRAN)
            return *iter;
        else
            return t;
    /*case ZERG:
        return *(Zerg.begin()+index-1);*/
    default:
        return t;
        break;
    }
}

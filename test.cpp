#include "unit.h"
#include <vector>
void test()
{
    std::vector<unit> abc;
    unit a;
    abc.push_back(a);
    std::vector<unit>::iterator iter=abc.begin();
}

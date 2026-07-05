#pragma once
#include "GridStructs.h"
#include <map>
class gridlogic
{
public:
    int gridwidth = 10;
    int gridheight = 10;
    std::map<coord, cell> gridmap ={};
    std::map<coord, cell> generategrid(bool debuggrid);
    void debug();
    gridlogic(int width, int height);
};

#pragma once
#include "GridStructs.h"
#include <map>
class GridLogic
{
public:
    int gridwidth = 10;
    int gridheight = 10;
    std::map<coord, cell> gridmap ={};
    std::map<coord, cell> generategrid(bool debuggrid);
    void debug();
    GridLogic(int width, int height);
};

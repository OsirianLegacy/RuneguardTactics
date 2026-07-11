#pragma once
#include "Data/GridStructs.h"
#include <map>
#include <vector>

class GridLogic
{
public:
    int gridwidth = 10;
    int gridheight = 10;
    std::map<coord, cell> gridmap ={};
    void generategrid(bool debuggrid);
    std::vector<coord> bfs(coord start, int depth, bool diagonals) const;
    std::vector<coord> getCellsInMovementRange(coord start, int movementRange, bool diagonals) const;
    std::vector<coord> getCellNeighbors(coord coord, bool diagonals) const;
    void debug();
    GridLogic(int width, int height);
};

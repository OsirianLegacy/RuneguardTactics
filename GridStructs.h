#pragma once
#include <iostream>
#include "GridEnums.h"
struct coord
{
    int x = 0;
    int y =0;
    auto operator<=>(const coord&) const = default;
    bool operator==(const coord&) const = default;
    coord(const int x, const int y)
    {
        this->x = x;
        this->y = y;
    }
};

struct cell
{
    coord coordinates = {0,0};
    bool walkable = false;
    int cost = 1;
    enum celltype type = celltype::empty;
};

struct gridlayout
{
    int startX;
    int startY;
    int tileSize;
    int gridWidth;
    int gridHeight;
};
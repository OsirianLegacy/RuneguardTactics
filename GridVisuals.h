//
// Created by Jkurt on 7/4/2026.
//

#ifndef RUNEGUARDTACTICS_GRIDVISUALS_H
#define RUNEGUARDTACTICS_GRIDVISUALS_H
#include <map>
#include "GridStructs.h"
class GridVisuals {
public:
    explicit GridVisuals(int tilesize, int screenwidth, int screenheight);
    int tileSize = 16;
    int screenWidth;
    int screenHeight;
    void updatevisuals(const std::map<coord, cell>& gridmap, int startX, int startY) const;
};


#endif //RUNEGUARDTACTICS_GRIDVISUALS_H
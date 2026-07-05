//
// Created by Jkurt on 7/4/2026.
//

#ifndef RUNEGUARDTACTICS_GRIDVISUALS_H
#define RUNEGUARDTACTICS_GRIDVISUALS_H
#include <map>
#include "GridStructs.h"
#include <vector>
#include <raylib.h>

#include "Colors.h"

class GridVisuals {
public:
    explicit GridVisuals(int tilesize, int screenwidth, int screenheight);
    int tileSize = 16;
    int screenWidth;
    int screenHeight;
    gridlayout gridLayout;
    std::vector<coord> highlightedCells;
    Color highlightColor = GameColors::MovementRange;
    void updateVisuals(const std::map<coord, cell>& gridmap, int startX, int startY) const;
    void setHighlightedCells(const std::vector<coord>& cells);
    void drawHighlightedCells();
    void setHighlightColor();
    Texture2D hoverTexture;
    void loadTextures();
    void unloadTextures() const;
    void drawHoveredCell(cell hoveredcell);
};


#endif //RUNEGUARDTACTICS_GRIDVISUALS_H
//
// Created by Jkurt on 7/4/2026.
//

#ifndef RUNEGUARDTACTICS_GRIDVISUALS_H
#define RUNEGUARDTACTICS_GRIDVISUALS_H
#include <map>
#include "Data/GridStructs.h"
#include <vector>
#include <raylib.h>
#include "GameState.h"

#include "Data/Colors.h"

class GridVisuals {
public:
    void setState(gamestate gamestate);
    explicit GridVisuals(int tilesize, int screenwidth, int screenheight);
    int tileSize = 16;
    int screenWidth;
    int screenHeight;
    gridlayout gridLayout;
    std::vector<coord> highlightedCells;
    Color highlightColor = GameColors::MovementRange;
    void updateVisuals(const std::map<coord, cell>& gridmap, int startX, int startY) const;
    void updateVisuals(const std::map<coord, cell>& gridmap, const gridlayout& layout) const;
    void setHighlightedCells(const std::vector<coord>& cells);
    void drawHighlightedCells();
    void drawHighlightedCells(const gridlayout& layout) const;
    void setHighlightColor();
    Texture2D hoverTexture;
    void loadTextures();
    void unloadTextures() const;
    void drawHoveredCell(cell hoveredcell) const;
    void drawHoveredCell(cell hoveredcell, const gridlayout& layout) const;

private:
    gamestate gameState = gamestate::mainmenu;
};


#endif //RUNEGUARDTACTICS_GRIDVISUALS_H

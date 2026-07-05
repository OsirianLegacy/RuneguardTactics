//
// Created by Jkurt on 7/4/2026.
//
#include <raylib.h>
#include "GridVisuals.h"
#include "GridStructs.h"
GridVisuals::GridVisuals(int tilesize, int screenwidth, int screenheight) {
    this->tileSize = tilesize;
    this->screenWidth = screenwidth;
    this->screenHeight = screenheight;
}

void GridVisuals::updatevisuals(const std::map<coord, cell>& gridmap, int startX, int startY) const {
    for (const auto& [coordinate,currentCell] : gridmap) {
        const int screenX = startX + coordinate.x * tileSize;
        const int screenY = startY + coordinate.y * tileSize;
        DrawRectangle(screenX, screenY, tileSize, tileSize, GRAY);
        DrawRectangleLines(screenX, screenY, tileSize, tileSize, {255, 255, 255, 5});
    }
}

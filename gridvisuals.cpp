//
// Created by Jkurt on 7/4/2026.
//
#include <raylib.h>
#include "gridvisuals.h"
#include "GridStructs.h"
gridvisuals::gridvisuals(int tilesize, int screenwidth, int screenheight) {
    this->tileSize = tilesize;
    this->screenWidth = screenwidth;
    this->screenHeight = screenheight;
}

void gridvisuals::updatevisuals(const std::map<coord, cell>& gridmap, int startX, int startY) const {
    for (const auto& [coordinate,currentCell] : gridmap) {
        const int screenX = startX + coordinate.x * tileSize;
        const int screenY = startY + coordinate.y * tileSize;
        DrawRectangle(screenX, screenY, tileSize, tileSize, GRAY);
        DrawRectangleLines(screenX, screenY, tileSize, tileSize, BLACK);
    }
}

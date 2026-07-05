//
// Created by Jkurt on 7/4/2026.
//
#include <raylib.h>
#include "GridVisuals.h"

#include "Colors.h"
#include "GridStructs.h"
GridVisuals::GridVisuals(int tilesize, int screenwidth, int screenheight) {
    this->tileSize = tilesize;
    this->screenWidth = screenwidth;
    this->screenHeight = screenheight;
}

void GridVisuals::updateVisuals(const std::map<coord, cell>& gridmap, int startX, int startY) const {
    for (const auto& [coordinate,currentCell] : gridmap) {
        const int screenX = startX + coordinate.x * tileSize;
        const int screenY = startY + coordinate.y * tileSize;
// remove grid fill       DrawRectangle(screenX, screenY, tileSize, tileSize, GRAY);
        DrawRectangleLines(screenX, screenY, tileSize, tileSize, GameColors::GridLine);
    }
}

void GridVisuals::updateVisuals(const std::map<coord, cell>& gridmap, const gridlayout& layout) const
{
    for (const auto& [coordinate,currentCell] : gridmap) {
        const int screenX = layout.startX + coordinate.x * layout.tileSize;
        const int screenY = layout.startY + coordinate.y * layout.tileSize;
        DrawRectangleLines(screenX, screenY, layout.tileSize, layout.tileSize, GameColors::GridLine);
    }
}


void GridVisuals::drawHoveredCell(cell hoveredcell)
{
    int startX = gridLayout.startX;
    int startY = gridLayout.startY;
    cell hoveredCell = hoveredcell;
    const int  screenX = startX + hoveredCell.coordinates.x * tileSize;
    const int  screenY = startY + hoveredCell.coordinates.y * tileSize;
    DrawTexture(hoverTexture, screenX, screenY, WHITE);
}

void GridVisuals::drawHoveredCell(cell hoveredcell, const gridlayout& layout) const
{
    const int screenX = layout.startX + hoveredcell.coordinates.x * layout.tileSize;
    const int screenY = layout.startY + hoveredcell.coordinates.y * layout.tileSize;

    Rectangle source = {
        0.0f,
        0.0f,
        static_cast<float>(hoverTexture.width),
        static_cast<float>(hoverTexture.height)
    };

    Rectangle dest = {
        static_cast<float>(screenX),
        static_cast<float>(screenY),
        static_cast<float>(layout.tileSize),
        static_cast<float>(layout.tileSize)
    };

    DrawTexturePro(hoverTexture, source, dest, Vector2{0, 0}, 0.0f, WHITE);
}

void GridVisuals::loadTextures()
{
    hoverTexture = LoadTexture("Assets/Art/Grid/Hover.png");
}

void GridVisuals::unloadTextures() const
{
    UnloadTexture(hoverTexture);
}

void GridVisuals::setHighlightedCells(const std::vector<coord> &cells)
{
    highlightedCells = cells;
}

void GridVisuals::drawHighlightedCells()
{
    for (coord coordinate : highlightedCells)
    {
        int screenX = gridLayout.startX + coordinate.x * tileSize;
        int screenY = gridLayout.startY + coordinate.y * tileSize;

        DrawRectangle(screenX, screenY, tileSize, tileSize, highlightColor);
    }
}

void GridVisuals::drawHighlightedCells(const gridlayout& layout) const
{
    for (coord coordinate : highlightedCells)
    {
        int screenX = layout.startX + coordinate.x * layout.tileSize;
        int screenY = layout.startY + coordinate.y * layout.tileSize;

        DrawRectangle(screenX, screenY, layout.tileSize, layout.tileSize, highlightColor);
    }
}

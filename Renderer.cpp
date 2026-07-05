//
// Created by Jkurt on 7/4/2026.
//

#include "Renderer.h"
#include <raylib.h>
#include "GridVisuals.h"
#include "GridLogic.h"
#include <map>

#include "InputManager_Combat.h"

Renderer::Renderer(int width, int height) {
 this->width = width;
 this->height = height;
}

void Renderer::render() const {
 std::map<coord, cell> gridmap = this->gridlogic->gridmap;
 int gridPixelWidth = gridlogic->gridwidth * gridvisuals->tileSize;
 int gridPixelHeight = gridlogic->gridheight * gridvisuals->tileSize;
 int startX = (width - gridPixelWidth) /2;
 int startY = (height - gridPixelHeight) /2;
 gridvisuals->updateVisuals(gridmap, startX, startY);
 auto hoveredcell = this->inputmanager->getHoveredCell();
 gridvisuals->drawHoveredCell(hoveredcell);
};

gridlayout Renderer::getGridLayout() const
{
 gridlayout gridLayout;
 int gridPixelWidth = gridlogic->gridwidth * gridvisuals->tileSize;
 int gridPixelHeight = gridlogic->gridheight * gridvisuals->tileSize;
 int startX = (width - gridPixelWidth) /2;
 int startY = (height - gridPixelHeight) /2;
 gridLayout.gridHeight = this->gridlogic->gridheight;
 gridLayout.gridWidth = this->gridlogic->gridwidth;
 gridLayout.startX = startX;
 gridLayout.startY = startY;
 gridLayout.tileSize = gridvisuals->tileSize;
 return gridLayout;
}
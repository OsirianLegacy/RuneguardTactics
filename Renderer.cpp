//
// Created by Jkurt on 7/4/2026.
//

#include "Renderer.h"
#include <raylib.h>
#include "GridVisuals.h"
#include "GridLogic.h"
#include <map>

#include "InputManager_Combat.h"
#include "TiledMap.h"

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
 // draw the map first
 tiledMap->draw(startX, startY);
 // draw highlights above the map
 gridvisuals->drawHighlightedCells();
 // draw the current hovered cell over highlights
 auto hoveredcell = this->inputmanager->getHoveredCell();
 gridvisuals->drawHoveredCell(hoveredcell);
 // render units above the current hovered cell.

 // then render objects since we want objects over units

 // draw grid outline last so it always shows the grid.
 gridvisuals->updateVisuals(gridmap, startX, startY);
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

void Renderer::setTileMap(TiledMap *tilemap) {
 this->tiledMap = tilemap;
}

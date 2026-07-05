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
 gridlayout layout = getGridLayout();
 int startX = layout.startX;
 int startY = layout.startY;
 gridvisuals->gridLayout = layout;
 // draw the map first
 if (tiledMap != nullptr)
 {
  tiledMap->draw(startX, startY, layout.tileSize);
 }
 // draw highlights above the map
 gridvisuals->drawHighlightedCells(layout);
 // draw the current hovered cell over highlights
 auto hoveredcell = this->inputmanager->getHoveredCell();
 gridvisuals->drawHoveredCell(hoveredcell, layout);
 // render units above the current hovered cell.

 // then render objects since we want objects over units

 // draw grid outline last so it always shows the grid.
 gridvisuals->updateVisuals(gridmap, layout);
};

gridlayout Renderer::getGridLayout() const
{
 gridlayout gridLayout;
 int scaledTileSize = static_cast<int>(gridvisuals->tileSize * renderScale);
 int gridPixelWidth = gridlogic->gridwidth * scaledTileSize;
 int gridPixelHeight = gridlogic->gridheight * scaledTileSize;
 int startX = (width - gridPixelWidth) /2;
 int startY = (height - gridPixelHeight) /2;
 gridLayout.gridHeight = this->gridlogic->gridheight;
 gridLayout.gridWidth = this->gridlogic->gridwidth;
 gridLayout.startX = startX;
 gridLayout.startY = startY;
 gridLayout.tileSize = scaledTileSize;
 return gridLayout;
}

void Renderer::setTileMap(TiledMap *tilemap) {
 this->tiledMap = tilemap;
}

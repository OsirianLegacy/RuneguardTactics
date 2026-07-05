//
// Created by Jkurt on 7/4/2026.
//

#include "renderer.h"
#include <raylib.h>
#include "gridvisuals.h"
#include "gridlogic.h"
#include <map>
renderer::renderer(int width, int height) {
 this->width = width;
 this->height = height;
}

void renderer::render() const {
 std::map<coord, cell> gridmap = this->gridlogic->gridmap;
 int gridPixelWidth = gridlogic->gridwidth * gridvisuals->tileSize;
 int gridPixelHeight = gridlogic->gridheight * gridvisuals->tileSize;
 int startX = (width - gridPixelWidth) /2;
 int startY = (height - gridPixelHeight) /2;
 gridvisuals->updatevisuals(gridmap, startX, startY);
};

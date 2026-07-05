//
// Created by Jkurt on 7/5/2026.
//

#ifndef RUNEGUARDTACTICS_TILEDSTRUCTS_H
#define RUNEGUARDTACTICS_TILEDSTRUCTS_H
#include <string>
#include <vector>
#include <raylib.h>
#include "GridEnums.h"
struct TiledLayer
{
    std::string name;
    int width = 0;
    int height = 0;
    bool visible = true;
    std::vector<int> data;
};

struct TiledTileset
{
    int firstGid = 1;
    Texture2D texture;
    int tileWidth = 32;
    int tileHeight = 32;
    int sourceTileWidth = 16;
    int sourceTileHeight = 16;
};

struct TiledTileProperties
{
    bool isObject = false;
    bool hasWalkable = false;
    bool walkable = false;
    bool hasCost = false;
    int cost = 0;
    bool hasCellType = false;
    celltype type = celltype::empty;
};

#endif //RUNEGUARDTACTICS_TILEDSTRUCTS_H

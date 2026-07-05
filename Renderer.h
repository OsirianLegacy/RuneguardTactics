//
// Created by Jkurt on 7/4/2026.
//

#ifndef RUNEGUARDTACTICS_RENDERER_H
#define RUNEGUARDTACTICS_RENDERER_H
#include "GridVisuals.h"
#include "GridLogic.h"

class InputManager_Combat;
class TiledMap;

class Renderer {
public:
    TiledMap* tiledMap = nullptr;
    Renderer(int width, int height);
    void render() const;
    [[nodiscard]] gridlayout getGridLayout() const;
    void setTileMap(TiledMap *tilemap);
    int width;
    int height;
    GridVisuals *gridvisuals;
    GridLogic *gridlogic;
    InputManager_Combat *inputmanager;
};


#endif //RUNEGUARDTACTICS_RENDERER_H

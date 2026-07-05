//
// Created by Jkurt on 7/4/2026.
//

#ifndef RUNEGUARDTACTICS_RENDERER_H
#define RUNEGUARDTACTICS_RENDERER_H
#include "CombatStructs.h"
#include "GridVisuals.h"
#include "GridLogic.h"

#include <vector>

class InputManager_Combat;
class TiledMap;

class Renderer {
public:
    TiledMap* tiledMap = nullptr;
    float renderScale = 1.75f;
    Renderer(int width, int height);
    void render() const;
    [[nodiscard]] gridlayout getGridLayout() const;
    void setTileMap(TiledMap *tilemap);
    void setActiveUnits(const std::vector<CombatUnit>* units);
    int width;
    int height;
    GridVisuals *gridvisuals;
    GridLogic *gridlogic;
    InputManager_Combat *inputmanager;
    const std::vector<CombatUnit>* activeUnits = nullptr;
};


#endif //RUNEGUARDTACTICS_RENDERER_H

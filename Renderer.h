//
// Created by Jkurt on 7/4/2026.
//

#ifndef RUNEGUARDTACTICS_RENDERER_H
#define RUNEGUARDTACTICS_RENDERER_H
#include "GridVisuals.h"
#include "GridLogic.h"
#include "InputManager_Combat.h"

class Renderer {
public:
    Renderer(int width, int height);
    void render() const;
    [[nodiscard]] gridlayout getGridLayout() const;
    int width;
    int height;
    GridVisuals *gridvisuals;
    GridLogic *gridlogic;
    InputManager_Combat *inputmanager;
};


#endif //RUNEGUARDTACTICS_RENDERER_H
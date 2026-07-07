//
// Created by Jkurt on 7/7/2026.
//

#ifndef RUNEGUARDTACTICS_GAMEUI_H
#define RUNEGUARDTACTICS_GAMEUI_H

#include <raylib.h>
#include "GameState.h"
class GameUI {
public:
    // the current state of the game.
    gamestate gameState = gamestate::mainmenu;
    void UpdateUI(gamestate gameState);
    void draw() const;
};

#endif //RUNEGUARDTACTICS_GAMEUI_H

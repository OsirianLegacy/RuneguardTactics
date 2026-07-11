//
// Created by Jkurt on 7/9/2026.
//

#ifndef RUNEGUARDTACTICS_UNITSELECTORUI_H
#define RUNEGUARDTACTICS_UNITSELECTORUI_H
#include "Widget/Button.h"
#include "GameState.h"
class unitSelectorUI
{
public:
    Button hireUnit;

    void draw();

    void update();

    explicit unitSelectorUI(
        const Texture2D& inButtonIdleTexture,
        const Texture2D& inButtonHoveredTexture,
        const Texture2D& inButtonClickedTexture,
        Font inFont);

    void setPosition(Vector2 newPosition);

    void setGameState(gamestate GameState);

private:
    gamestate gameState = gamestate::mainmenu;
    Font alagard{};
};


#endif //RUNEGUARDTACTICS_UNITSELECTORUI_H

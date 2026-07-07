#include "GameUI.h"
#include <raylib.h>

void GameUI::UpdateUI(gamestate gameState) {
    this->gameState = gameState;
}

void GameUI::draw() const
{
    if (gameState == gamestate::mainmenu)
    {
        DrawRectangle(100, 100, 200, 80, RED);
    }
}

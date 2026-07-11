//
// Created by Jkurt on 7/9/2026.
//

#include "UnitSelectorUI.h"

unitSelectorUI::unitSelectorUI(
    const Texture2D& inButtonIdleTexture,
    const Texture2D& inButtonHoveredTexture,
    const Texture2D& inButtonClickedTexture,
    Font inFont)
    : alagard(inFont)
{
    hireUnit = Button(ButtonData{
        {-100.0f, -100.0f},
        inButtonIdleTexture,
        inButtonHoveredTexture,
        inButtonClickedTexture,
        gameevent::hireunit,
        false,
        gamestate::newgameunitselector,
        true,
        "Hire Unit",
        alagard
    });
    hireUnit.getData().visible = true;
}

void unitSelectorUI::setGameState(const gamestate GameState)
{
    gameState = GameState;
}

void unitSelectorUI::setPosition(Vector2 newPosition)
{
    hireUnit.setPosition(newPosition);
}

void unitSelectorUI::draw()
{
    if(gameState == gamestate::newgameunitselector)
    {
        hireUnit.setPosition({500,500});
        hireUnit.getData().visible = true;
        hireUnit.draw();

    }
}

void unitSelectorUI::update()
{
    hireUnit.update(GetMousePosition(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT), IsMouseButtonDown(MOUSE_BUTTON_LEFT));
}

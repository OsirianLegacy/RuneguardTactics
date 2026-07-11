#include "GameUI.h"
#include <raylib.h>
#include <iostream>
#include <memory>

GameUI::GameUI(Renderer& inrenderer, InputManager& ininputManager)
    : renderer(inrenderer), inputManager(ininputManager)
{
}

void GameUI::UpdateUI(gamestate gameState)
{
    this->gameState = gameState;
    if (mainMenuScreen)
    {
        mainMenuScreen->setGameState(gameState);
    }
    if (unitSelectorScreen)
    {
        unitSelectorScreen->setGameState(gameState);
    }
}

void GameUI::loadTextures()
{
    buttonIdleTexture = LoadTexture("Assets/Art/UI/T_Button_Idle.png");
    buttonHoveredTexture = LoadTexture("Assets/Art/UI/T_Button_Hovered.png");
    buttonClickedTexture = LoadTexture("Assets/Art/UI/T_Button_Clicked.png");
    titleScreenTexture = LoadTexture("Assets/Art/UI/T_TitleScreen.png");
    backgroundTexture4K = LoadTexture("Assets/Art/UI/T_Background_4K.png");
}

void GameUI::loadFonts()
{
    alagard = LoadFontEx("Assets/Fonts/alagard.ttf", 64, nullptr, 0);
    SetTextureFilter(alagard.texture, TEXTURE_FILTER_POINT);
    createScreens();
}

void GameUI::createScreens()
{
    mainMenuScreen = std::make_unique<MainMenuUI>(
        renderer,
        inputManager,
        titleScreenTexture,
        buttonIdleTexture,
        buttonHoveredTexture,
        buttonClickedTexture,
        alagard);
    mainMenuScreen->setGameState(gameState);

    unitSelectorScreen = std::make_unique<unitSelectorUI>(
        buttonIdleTexture,
        buttonHoveredTexture,
        buttonClickedTexture,
        alagard);
    unitSelectorScreen->setPosition({500.0f, 500.0f});
    unitSelectorScreen->setGameState(gameState);
}

    GameUI::UIAnchors GameUI::getAnchors() const
{
    const float width = static_cast<float>(renderer.width);
    const float height = static_cast<float>(renderer.height);

    return UIAnchors{
        .topLeft = { 0.0f, 0.0f },
        .top = { width / 2.0f, 0.0f },
        .topRight = { width, 0.0f },

        .left = { 0.0f, height / 2.0f },
        .center = { width / 2.0f, height / 2.0f },
        .right = { width, height / 2.0f },

        .bottomLeft = { 0.0f, height },
        .bottom = { width / 2.0f, height },
        .bottomRight = { width, height }
    };
}

gameevent GameUI::getGameEvent() const {
    return nextGameEvent;
}

void GameUI::setGameEvent(const gameevent newGameEvent) {
    nextGameEvent = newGameEvent;
}

void GameUI::draw()
{
    if (gameState == gamestate::mainmenu)
    {
        if (mainMenuScreen)
        {
            mainMenuScreen->draw();
        }
    }
    if (gameState == gamestate::newgameunitselector)
    {
        DrawTexture(backgroundTexture4K, 0,0, WHITE);
        if (unitSelectorScreen)
        {
            unitSelectorScreen->draw();
        }
    }

}

void GameUI::update()
{
    if (mainMenuScreen)
    {
        if (const gameevent event = mainMenuScreen->update(); event != gameevent::null)
        {
            setGameEvent(event);
        }
    }

    if (unitSelectorScreen)
    {
        unitSelectorScreen->update();
    }
}


void GameUI::setGameState(gamestate newGameState) {
    gameState = newGameState;
    UpdateUI(gameState);
}

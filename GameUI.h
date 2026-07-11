//
// Created by Jkurt on 7/7/2026.
//

#ifndef RUNEGUARDTACTICS_GAMEUI_H
#define RUNEGUARDTACTICS_GAMEUI_H

#include <memory>
#include <raylib.h>
#include "GameState.h"
#include "Renderer.h"
#include "InputManager.h"
#include "MainMenuUI.h"
#include "UnitSelectorUI.h"

class GameUI {

public:
    struct UIAnchors
    {
        Vector2 topLeft{};
        Vector2 top{};
        Vector2 topRight{};

        Vector2 left{};
        Vector2 center{};
        Vector2 right{};

        Vector2 bottomLeft{};
        Vector2 bottom{};
        Vector2 bottomRight{};
    };

    GameUI(Renderer& inrenderer, InputManager& ininputManager);
    // the current state of the game.
    gamestate gameState = gamestate::mainmenu;
    void loadFonts();
    void UpdateUI(gamestate gameState);
    void draw();
    void update();
    void loadTextures();
    void setGameState(gamestate newGameState);
    void setGameEvent(gameevent newGameEvent);
    gameevent getGameEvent() const;

private:
    // REFS
    Renderer& renderer;
    InputManager& inputManager;

    // UI Screens
    std::unique_ptr<MainMenuUI> mainMenuScreen;
    std::unique_ptr<unitSelectorUI> unitSelectorScreen;

    //UI Variables
    void createScreens();
    UIAnchors getAnchors() const;
    UIAnchors anchors = getAnchors();

    // Shared UI Textures
    Texture2D buttonIdleTexture = {};
    Texture2D buttonHoveredTexture = {};
    Texture2D buttonClickedTexture = {};
    Texture2D titleScreenTexture = {};

    // New Game Unit Creation UI
    Texture2D backgroundTexture4K = {};


    // Fonts
    Font alagard = {};

    // Non-UI Variables
    gameevent nextGameEvent = gameevent::null;
};

#endif //RUNEGUARDTACTICS_GAMEUI_H

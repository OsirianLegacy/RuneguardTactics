//
// Created by Jkurt on 7/7/2026.
//

#ifndef RUNEGUARDTACTICS_GAMEUI_H
#define RUNEGUARDTACTICS_GAMEUI_H

#include <raylib.h>
#include "GameState.h"
#include "Renderer.h"
#include "InputManager.h"

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
    void update() const;
    void loadTextures();
    void setGameState(gamestate newGameState);
    void setGameEvent(gameevent newGameEvent);
    gameevent getGameEvent() const;

private:
    // REFS
    Renderer& renderer;
    InputManager& inputManager;

    //UI Variables
    UIAnchors getAnchors() const;
    UIAnchors anchors = getAnchors();

    // Main Menu UI
    Texture2D buttonNewGameTexture = {};
    Texture2D buttonNewGameHoveredTexture = {};
    Texture2D buttonNewGameClickedTexture = {};
    Texture2D buttonContinueGameTexture = {};
    Texture2D buttonContinueGameHoveredTexture = {};
    Texture2D buttonContinueGameClickedTexture = {};
    Texture2D titleScreenTexture = {};

    // New Game Unit Creation UI
    Texture2D backgroundTexture4K = {};


    // Fonts
    Font alagard = {};

    // Non-UI Variables
    gameevent nextGameEvent = gameevent::null;

    const Vector2 center {
        renderer.width / 2.0f,
        renderer.height / 2.0f
    };

    const Vector2 titlePos {
        anchors.topLeft.x,
        anchors.topLeft.y
    };

    const Vector2 newGameButtonPos {
        center.x-100,
        center.y
    };

    const Vector2 continueButtonPos {
        center.x-100,
        center.y+75
    };
};

#endif //RUNEGUARDTACTICS_GAMEUI_H

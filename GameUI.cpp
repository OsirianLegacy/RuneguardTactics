#include "GameUI.h"
#include <raylib.h>
#include <iostream>
GameUI::GameUI(Renderer& inrenderer, InputManager& ininputManager)
    : renderer(inrenderer), inputManager(ininputManager)
{
}

void GameUI::UpdateUI(gamestate gameState)
{
    this->gameState = gameState;
}

void GameUI::loadTextures()
{
    buttonNewGameTexture = LoadTexture("Assets/Art/UI/T_Button_NewGame_Idle.png");
    buttonNewGameHoveredTexture = LoadTexture("Assets/Art/UI/T_Button_NewGame_Hovered.png");
    buttonNewGameClickedTexture = LoadTexture("Assets/Art/UI/T_Button_NewGame_Clicked.png");
    buttonContinueGameTexture = LoadTexture("Assets/Art/UI/T_Button_Continue_Idle.png");
    buttonContinueGameHoveredTexture = LoadTexture("Assets/Art/UI/T_Button_Continue_Hovered.png");
    buttonContinueGameClickedTexture = LoadTexture("Assets/Art/UI/T_Button_Continue_Clicked.png");
    titleScreenTexture = LoadTexture("Assets/Art/UI/T_TitleScreen.png");
    backgroundTexture4K = LoadTexture("Assets/Art/UI/T_Background_4K.png");
}

void GameUI::loadFonts()
{
    alagard = LoadFontEx("Assets/Fonts/alagard.ttf", 64, nullptr, 0);
    SetTextureFilter(alagard.texture, TEXTURE_FILTER_POINT);
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
        // draw the background title screen first. This ensures other elements are drawn on top of it.
        DrawTexture(titleScreenTexture, titlePos.x, titlePos.y, WHITE);

        // check mouse position every frame
        Vector2 mousePosition = inputManager.getMousePosition();

        // create collider for newGameButton
        Rectangle newGameButtonRect
        {
        newGameButtonPos.x, newGameButtonPos.y,
            static_cast<float>(buttonNewGameTexture.width),
            static_cast<float>(buttonNewGameTexture.height)
        };

        // create collider for ContinueGameButton
        Rectangle ContinueGameButtonRect
        {
            continueButtonPos.x, continueButtonPos.y,
                static_cast<float>(buttonNewGameTexture.width),
                static_cast<float>(buttonNewGameTexture.height)
        };
        // Check if mouse is in the newGameButtonRect
        bool isHoveringNewGameButton = CheckCollisionPointRec(mousePosition, newGameButtonRect);

        // Check if mouse is in the ContinueGameButtonRect
        bool isHoveringContinueGameButton = CheckCollisionPointRec(mousePosition, ContinueGameButtonRect);

        // Set the Textures for New and Continue Game Buttons
        Texture2D newGameTexture = buttonNewGameTexture;
        Texture2D continueGameTexture = buttonContinueGameTexture;

        // Check if the mouse is Hovering over the New Game Button
        if (isHoveringNewGameButton)
        {
            newGameTexture = buttonNewGameHoveredTexture;

            if (inputManager.isLeftMouseDown())
            {
                newGameTexture = buttonNewGameClickedTexture;
                if (nextGameEvent != gameevent::newgame)
                {
                    setGameEvent(gameevent::newgame);
                    std::cout << "player clicked new game\n";
                }

            }
        }
        // Check if the mouse is Hovering over the Continue Game Button
        if (isHoveringContinueGameButton)
        {
            continueGameTexture = buttonContinueGameHoveredTexture;
            if (inputManager.isLeftMouseDown())
            {
                continueGameTexture = buttonContinueGameClickedTexture;
                if (nextGameEvent != gameevent::continuegame)
                {
                    setGameEvent(gameevent::continuegame);
                    std::cout << "player clicked continue game\n";
                }

            }
        }
        DrawTexture(newGameTexture, newGameButtonPos.x, newGameButtonPos.y, WHITE);
        DrawTexture(continueGameTexture, continueButtonPos.x, continueButtonPos.y, WHITE);
    }
    if (gameState == gamestate::newgameunitselector)
    {
        DrawTexture(backgroundTexture4K, 0,0, WHITE);
        DrawRectangle(anchors.center.x+)
    }

}

void GameUI::update() const
{

}


void GameUI::setGameState(gamestate newGameState) {
    gameState = newGameState;
    UpdateUI(gameState);
}


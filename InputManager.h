//
// Created by Jkurt on 7/4/2026.
//

#ifndef RUNEGUARDTACTICS_INPUTMANAGER_H
#define RUNEGUARDTACTICS_INPUTMANAGER_H
#include <raylib.h>
#include "Data/GridStructs.h"
#include "GameState.h"

class Renderer;

class InputManager {
public:
    void setState(gamestate newGameState);

    void setGameState(gamestate newGameState);
    void setGameEvent(gameevent newGameEvent);
    explicit InputManager(Renderer& inputrenderer);
    [[nodiscard]] static Vector2 getMousePosition() ;
    [[nodiscard]] cell getHoveredCell() const;
    [[nodiscard]] cell getClickedCell() const;
    [[nodiscard]] static bool isMouseInWindow() ;
    [[nodiscard]] static bool wasLeftClicked();
    [[nodiscard]] static bool isLeftMouseDown();
    [[nodiscard]] static bool wasRightClicked();
    [[nodiscard]] static bool wasSpacePressed();
    void resolveLeftClick();
    void resolveRightClick();
    bool isMouseInGrid();
    void update();


private:
    cell previousCell;
    cell hoveredCell;
    cell clickedCell = {{0,0}, false, false, 1, celltype::empty};
    void setHoveredCell();
    Renderer& renderer;
    gameevent currentGameEvent = gameevent::null;
    gamestate gameState = gamestate::mainmenu;

};


#endif //RUNEGUARDTACTICS_INPUTMANAGER_H

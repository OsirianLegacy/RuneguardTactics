//
// Created by Jkurt on 7/4/2026.
//

#ifndef RUNEGUARDTACTICS_INPUTMANAGER_H
#define RUNEGUARDTACTICS_INPUTMANAGER_H
#include <raylib.h>
#include "GridStructs.h"

class Renderer;

class InputManager_Combat {
public:
    explicit InputManager_Combat(Renderer& inputrenderer);
    [[nodiscard]] static Vector2 getMousePosition() ;
    [[nodiscard]] cell getHoveredCell() const;
    [[nodiscard]] static bool isMouseInWindow() ;
    [[nodiscard]] static bool wasLeftClicked();
    [[nodiscard]] static bool wasRightClicked();
    [[nodiscard]] static bool wasSpacePressed();
    void update();

private:
    cell previousCell;
    cell hoveredCell;
    void setHoveredCell();
    bool isMouseInGrid();
    Renderer& renderer;
};


#endif //RUNEGUARDTACTICS_INPUTMANAGER_H

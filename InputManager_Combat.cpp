//
// Created by Jkurt on 7/4/2026.
//

#include "InputManager_Combat.h"
#include <raylib.h>
#include "Renderer.h"
#include "GridStructs.h"

InputManager_Combat::InputManager_Combat(Renderer& inputrenderer)
    : renderer(inputrenderer)
{
}

Vector2 InputManager_Combat::getMousePosition()
{
    return GetMousePosition();
}

void InputManager_Combat::setHoveredCell()
{
    auto mouse = getMousePosition();
    if (auto inWindow = isMouseInWindow() && (isMouseInGrid()))
    {
        gridlayout gridLayout = renderer.getGridLayout();
        const int localMouseX = mouse.x - gridLayout.startX;
        const int localMouseY = mouse.y - gridLayout.startY;

        int gridX = localMouseX / gridLayout.tileSize;
        int gridY = localMouseY / gridLayout.tileSize;
        coord hoveredCoord{gridX, gridY};
        if (renderer.gridlogic->gridmap.contains(hoveredCoord)) {
            hoveredCell = renderer.gridlogic->gridmap.at(hoveredCoord);
        }
    }
}


cell InputManager_Combat::getHoveredCell() const {
    return hoveredCell;
}


bool InputManager_Combat::isMouseInWindow()
{
    Vector2 mousePosition = getMousePosition();
    bool mouseInWindow =
        mousePosition.x >= 0 &&
            mousePosition.y >= 0 &&
                mousePosition.x < GetScreenWidth() &&
                    mousePosition.y < GetScreenHeight();
    return mouseInWindow;
}

bool InputManager_Combat::isMouseInGrid()
{
    auto mouse = getMousePosition();
    gridlayout gridLayout = renderer.getGridLayout();
    bool mouseInGrid =
        mouse.x >= gridLayout.startX &&
            mouse.y >= gridLayout.startY &&
                mouse.x < gridLayout.startX + gridLayout.gridWidth * gridLayout.tileSize &&
                    mouse.y < gridLayout.startY + gridLayout.gridHeight * gridLayout.tileSize;
    return mouseInGrid;
}

bool InputManager_Combat::wasLeftClicked() {
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool InputManager_Combat::wasRightClicked() {
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
}

bool InputManager_Combat::wasSpacePressed() {
    return IsKeyPressed(KEY_SPACE);
}

//
// Created by Jkurt on 7/4/2026.
//

#include "InputManager.h"
#include <raylib.h>
#include "Renderer.h"
#include "GridStructs.h"
#include <iostream>

InputManager::InputManager(Renderer& inputrenderer)
    : renderer(inputrenderer)
{
}

void InputManager::setState(gamestate gameState) {
    this->gameState = gameState;
}


Vector2 InputManager::getMousePosition()
{
    return GetMousePosition();
}

void InputManager::setHoveredCell()
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


cell InputManager::getHoveredCell() const
{
    return hoveredCell;
}


bool InputManager::isMouseInWindow()
{
    Vector2 mousePosition = getMousePosition();
    bool mouseInWindow =
        mousePosition.x >= 0 &&
            mousePosition.y >= 0 &&
                mousePosition.x < GetScreenWidth() &&
                    mousePosition.y < GetScreenHeight();
    return mouseInWindow;
}

bool InputManager::isMouseInGrid()
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

void InputManager::update()
{
    if (gameState == gamestate::mainmenu)
    {

    }

    // If we're in Combat, we should be setting the hovered cell every tick.
    if (gameState == gamestate::combat)
    {
        this->setHoveredCell();
    }

}


bool InputManager::wasLeftClicked()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void InputManager::resolveLeftClick()
{
    if (isMouseInWindow() && isMouseInGrid())
    {
        if (bool leftclicked = wasLeftClicked())
        {
            clickedCell = getHoveredCell();
            std::cout << "Cell was clicked: " << clickedCell.coordinates.x << "," << clickedCell.coordinates.y << "\n";
        }
    }
}

cell InputManager::getClickedCell() const
{
    return clickedCell;
}


bool InputManager::wasRightClicked()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
}

bool InputManager::wasSpacePressed()
{
    return IsKeyPressed(KEY_SPACE);
}

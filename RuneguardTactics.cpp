#include <iostream>
#include "CombatManager.h"
#include "Debugtools.h"
#include "GridLogic.h"
#include "GridVisuals.h"
#include "Renderer.h"
#include <raylib.h>
#include "InputManager.h"
#include "Missions.h"
#include "TiledMap.h"
#include "GameState.h"
#include "GameUI.h"
using namespace debugtools;

GridLogic grid(16,16);
Renderer renderer(1600, 900);
int width = renderer.width;
int height = renderer.height;
GridVisuals visuals(32, width, height);
InputManager input(renderer);
coord clickedCoords = {0,0};
GameState state;
GameUI UI;

int main()
{
    // pass through renderer variables prior to rendering
    int width = renderer.width;
    int height = renderer.height;
    renderer.gridlogic = &grid;
    renderer.gridvisuals = &visuals;
    renderer.inputmanager = &input;
    visuals.highlightColor = GameColors::AttackRange;
    state.setGameState(gamestate::mainmenu);
    input.setState(state.getGameState());
    UI.UpdateUI(gamestate::mainmenu);
    // Game Loop starts here, load textures here before using.
    InitWindow(width, height, "Rune Guard Tactics");
    visuals.loadTextures();
    MissionDatabase missionDatabase;


    while (!WindowShouldClose()) {
        input.update();
        input.resolveLeftClick();
        if (InputManager::wasLeftClicked() && input.isMouseInGrid())
        {
            cell cellClicked = input.getClickedCell();
            clickedCoords = cellClicked.coordinates;
            std::vector<coord> neighbors = grid.getCellNeighbors(clickedCoords, true);
            std::cout << clickedCoords.x << "," << clickedCoords.y << ":" << " has Neighbors: " << neighbors.size() << "\n";
            visuals.setHighlightedCells(grid.getCellsInMovementRange(clickedCoords, 5, false));
        };

        BeginDrawing();
        ClearBackground(BLACK);
        renderer.render();
        UI.draw();


        EndDrawing();
    }
    visuals.unloadTextures();
    CloseWindow();
    return 0;
}

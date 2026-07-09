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
#include "GameEvents.h"
using namespace debugtools;

GridLogic grid(16,16);
Renderer renderer(1600, 900);
int width = renderer.width;
int height = renderer.height;
GridVisuals visuals(32, width, height);
InputManager input(renderer);
coord clickedCoords = {0,0};
GameState state;
GameUI UI(renderer, input);

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
    UI.setGameEvent(gameevent::null);

// ------Window hasn't opened yet, don't load textures before this point------ //
    InitWindow(width, height, "Rune Guard Tactics");
    visuals.loadTextures();
    UI.loadTextures();
    UI.loadFonts();
    MissionManager missionManager;
    MissionDatabase missionDatabase;
    CombatManager combatManager(grid);
    GameEvents events{combatManager, state, input, UI, missionManager};
    events.currentGameEvent = gameevent::null;
// ------Game Loop starts here, load textures before this point------ //
    while (!WindowShouldClose()) {
        events.checkGameEvent(UI.getGameEvent());
        events.checkGameState(state.getGameState());
        input.update();
        input.resolveLeftClick();

        // Gate left click cell fetching unless game state is in combat.
        if (InputManager::wasLeftClicked() && input.isMouseInGrid() && state.getGameState() == gamestate::combat)
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

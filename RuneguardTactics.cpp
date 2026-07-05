#include <iostream>
#include "Debugtools.h"
#include "GridLogic.h"
#include "GridVisuals.h"
#include "Renderer.h"
#include <raylib.h>
#include "InputManager_Combat.h"
#include "TiledMap.h"
using namespace debugtools;

GridLogic grid(16,16);
Renderer renderer(1600, 900);
int width = renderer.width;
int height = renderer.height;
GridVisuals visuals(32, width, height);
InputManager_Combat input(renderer);
coord clickedCoords = {0,0};
TiledMap GameMap;
int main()
{
    int width = renderer.width;
    int height = renderer.height;
    grid.generategrid(false);
    renderer.gridlogic = &grid;
    renderer.gridvisuals = &visuals;
    renderer.inputmanager = &input;
    visuals.gridLayout = renderer.getGridLayout();
    GameMap.loadFromJson("Assets/Maps/DuskFerrets_Hideout_Entrance.json");
    GameMap.loadTilesetFromTsx("Assets/Art/Tilesets/DuskFerrets_Hideout.tsx");
    GameMap.initializeGrid(grid, "Walls");
    renderer.tiledMap = &GameMap;
    visuals.highlightColor = GameColors::AttackRange;
    // Game Loop starts here, load textures here before using.
    InitWindow(width, height, "Rune Guard Tactics");
    visuals.loadTextures();
    GameMap.loadTilesetTexture("Assets/Art/Tilesets/DuskFerrets_Hideout_Entrance.png");
    while (!WindowShouldClose()) {
        input.update();
        input.resolveLeftClick();
        if (InputManager_Combat::wasLeftClicked() && input.isMouseInGrid())
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


        EndDrawing();
    }
    visuals.unloadTextures();
    GameMap.unloadTextures();
    CloseWindow();
    return 0;
}




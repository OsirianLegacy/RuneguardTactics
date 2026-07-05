#include <iostream>
#include "Debugtools.h"
#include "GridLogic.h"
#include "GridVisuals.h"
#include "Renderer.h"
#include <raylib.h>
#include "InputManager_Combat.h"
using namespace debugtools;

GridLogic grid(16,16);
Renderer renderer(1024, 768);
InputManager_Combat input(renderer);
int width = renderer.width;
int height = renderer.height;
GridVisuals visuals(32, width, height);
int main()
{
    int width = renderer.width;
    int height = renderer.height;
    grid.generategrid(false);
    renderer.gridlogic = &grid;
    renderer.gridvisuals = &visuals;

    InitWindow(width, height, "Rune Guard Tactics");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        renderer.render();


        EndDrawing();
    }

    CloseWindow();
    return 0;
}




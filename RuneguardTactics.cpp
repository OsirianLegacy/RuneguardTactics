#include <iostream>
#include "debugtools.h"
#include "gridlogic.h"
#include "gridvisuals.h"
#include "renderer.h"
#include <raylib.h>
using namespace debugtools;

gridlogic grid(16,16);
renderer renderer(1024, 768);
int width = renderer.width;
int height = renderer.height;
gridvisuals visuals(32, width, height);
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




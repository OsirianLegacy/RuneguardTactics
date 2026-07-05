#include <iostream>
#include "CombatManager.h"
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
// Temporary to test Mission Loads working
MissionData createDuskFerretsMission()
{
    MissionData mission;
    mission.missionId = "dusk_ferrets";
    mission.missionName = "Dusk Ferrets";
    mission.missionDescription = "Clear the Dusk Ferrets hideout entrance.";

    EncounterData entranceEncounter;
    entranceEncounter.encounterId = "dusk_ferrets_hideout_entrance";
    entranceEncounter.mapData.mapId = "dusk_ferrets_hideout_entrance";
    entranceEncounter.mapData.mapJsonPath = "Assets/Maps/DuskFerrets_Hideout_Entrance.json";
    entranceEncounter.mapData.tilesetPath = "Assets/Art/Tilesets/DuskFerrets_Hideout.tsx";
    entranceEncounter.mapData.tilesetTexturePath = "Assets/Art/Tilesets/DuskFerrets_Hideout_Entrance.png";
    entranceEncounter.mapData.walkableLayerName = "Ground";
    entranceEncounter.mapData.blockedLayerName = "Walls";
    entranceEncounter.mapData.objectLayerName = "Objects";

    mission.encounters.push_back(entranceEncounter);
    return mission;
}

int main()
{
    int width = renderer.width;
    int height = renderer.height;
    renderer.gridlogic = &grid;
    renderer.gridvisuals = &visuals;
    renderer.inputmanager = &input;
    visuals.highlightColor = GameColors::AttackRange;

    // Game Loop starts here, load textures here before using.
    InitWindow(width, height, "Rune Guard Tactics");
    visuals.loadTextures();

    CombatManager combatManager(grid);
    MissionData mission = createDuskFerretsMission();

    if (!combatManager.startMissionEncounter(mission, "dusk_ferrets_hideout_entrance"))
    {
        CloseWindow();
        return 1;
    }

    renderer.tiledMap = &combatManager.getCurrentMap();
    renderer.setActiveUnits(&combatManager.getActiveUnits());
    visuals.gridLayout = renderer.getGridLayout();

    while (!WindowShouldClose()) {
        combatManager.update(GetFrameTime());
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
    combatManager.getCurrentMap().unloadTextures();
    CloseWindow();
    return 0;
}



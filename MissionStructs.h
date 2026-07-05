//
// Created by Jkurt on 7/5/2026.
//

#ifndef RUNEGUARDTACTICS_MISSIONSTRUCTS_H
#define RUNEGUARDTACTICS_MISSIONSTRUCTS_H
#include <string>
#include "GridStructs.h"
#include "Units/Stats/UnitDefinition.h"
#include <vector>
// Encounters read this and set the Map to Render to the Renderer.
struct TiledMapData
{
    std::string mapId;
    std::string mapJsonPath;
    std::string tilesetPath;
    std::string tilesetTexturePath;
    std::string walkableLayerName = "Ground";
    std::string blockedLayerName = "Walls";
    std::string objectLayerName = "Objects";
};

struct DeploymentSlot
{
    std::string slotId;
    coord position;
};

// Systems can feed Spawner these SpawnRequests
struct EncounterSpawn
{
    std::string spawnId;
    std::string unitId;
    coord position;
    TEAM teamOverride;
};

// Missions are comprised of 1 or More Encounters.
// This Data is used by the GameManager -> CombatManager what to do.
// Combat Manager then reads this data and readies the Encounter.
struct EncounterData
{
    std::string encounterId;
    TiledMapData mapData;
    std::vector<DeploymentSlot> playerDeploymentSlots;
    std::vector<EncounterSpawn> encounterSpawns;
};

struct MissionData
{
    std::string missionId;
    std::string missionName;
    std::string missionDescription;
    std::vector<EncounterData> encounters;
};
#endif //RUNEGUARDTACTICS_MISSIONSTRUCTS_H

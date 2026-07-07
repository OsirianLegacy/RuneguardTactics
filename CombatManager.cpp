#include "CombatManager.h"

#include <iostream>
#include <utility>

CombatManager::CombatManager(
    GridLogic& grid,
    std::filesystem::path unitDatabaseDirectory)
    : unitFactory(std::move(unitDatabaseDirectory)),
      spawner(unitFactory),
      grid(&grid)
{
}
// Verifies all Encounter Data is valid, and reports back if anything is a nullptr or has invalid data
// Sends console debug to assist with figuring out where issues are, fails at each necessary point.
bool CombatManager::startMissionEncounter(const MissionData& mission, const std::string& encounterId)
{
    // CombatManager calls its function findEncounter passing through the mission & encounterId to locate and set its variables.
    const EncounterData* encounter = findEncounter(mission, encounterId);

    if (encounter == nullptr)
    {
        std::cout << "Failed to start encounter: '" << encounterId
            << "' was not found in mission '" << mission.missionId << "'.\n";
        return false;
    }

    combatState = CombatState{};
    combatState.encounter = *encounter;

    if (!currentMap.loadFromJson(encounter->mapData.mapJsonPath))
    {
        std::cout << "Failed to start encounter '" << encounter->encounterId
            << "': map JSON could not be loaded.\n";
        return false;
    }

    if (!encounter->mapData.tilesetPath.empty() &&
        !currentMap.loadTilesetFromTsx(encounter->mapData.tilesetPath))
    {
        std::cout << "Failed to start encounter '" << encounter->encounterId
            << "': tileset could not be loaded.\n";
        return false;
    }

    currentMap.initializeGrid(
        *grid,
        encounter->mapData.walkableLayerName,
        encounter->mapData.blockedLayerName,
        encounter->mapData.objectLayerName);

    combatState.playerDeploymentSlots = currentMap.getDeploymentSlots();
    const SpawnReport report =
        spawner.spawnEncounter(*encounter, currentMap, *grid, combatState.activeUnits);

    std::cout << "Encounter '" << encounter->encounterId << "' started. Spawned "
        << report.spawnedUnits << " of " << report.requestedSpawns
        << " requested units; skipped " << report.skippedSpawns << ".\n";

    if (!encounter->mapData.tilesetTexturePath.empty())
    {
        currentMap.loadTilesetTexture(encounter->mapData.tilesetTexturePath);
    }

    return true;
}
// Handles animating Units based on their Sprite Sheet.
void CombatManager::update(const float deltaTime)
{
    if (deltaTime <= 0.0f)
    {
        return;
    }

    for (CombatUnit& combatUnit : combatState.activeUnits)
    {
        if (combatUnit.animationFramesPerSecond <= 0.0f)
        {
            continue;
        }

        const float secondsPerFrame = 1.0f / combatUnit.animationFramesPerSecond;
        combatUnit.animationTimer += deltaTime;

        while (combatUnit.animationTimer >= secondsPerFrame)
        {
            combatUnit.animationTimer -= secondsPerFrame;
            combatUnit.animationFrame = (combatUnit.animationFrame + 1) % 4;
        }
    }
}

const std::vector<CombatUnit>& CombatManager::getActiveUnits() const
{
    return combatState.activeUnits;
}

const std::vector<DeploymentSlot>& CombatManager::getPlayerDeploymentSlots() const
{
    return combatState.playerDeploymentSlots;
}

TiledMap& CombatManager::getCurrentMap()
{
    return currentMap;
}

const TiledMap& CombatManager::getCurrentMap() const
{
    return currentMap;
}

const CombatState& CombatManager::getCombatState() const
{
    return combatState;
}
// loops through a Missions Encounters and checks if one of those Encounters are its current EncounterID. If false, it returns nullptr
const EncounterData* CombatManager::findEncounter(
    const MissionData& mission,
    const std::string& encounterId) const
{
    for (const EncounterData& encounter : mission.encounters)
    {
        if (encounter.encounterId == encounterId)
        {
            return &encounter;
        }
    }
    std::cout << "EncounterID not found in combat state\n";
    return nullptr;
}

#include "Spawner.h"

#include <exception>
#include <iostream>

Spawner::Spawner(UnitFactory& unitFactory)
    : unitFactory(unitFactory)
{
}

SpawnReport Spawner::spawnEncounter(
    const EncounterData& encounter,
    const TiledMap& map,
    GridLogic& grid,
    std::vector<CombatUnit>& activeUnits) const
{
    SpawnReport report;
    const std::vector<DeploymentSlot> deploymentSlots = map.getDeploymentSlots();
    const std::vector<EncounterSpawn> encounterSpawns = map.getEncounterSpawns();
    report.requestedSpawns = static_cast<int>(encounterSpawns.size());

    std::cout << "Spawner loaded " << deploymentSlots.size()
        << " player deployment slots for encounter '" << encounter.encounterId << "'.\n";

    for (const EncounterSpawn& spawn : encounterSpawns)
    {
        if (!grid.gridmap.contains(spawn.position))
        {
            std::cout << "Skipping spawn '" << spawn.spawnId << "': grid cell "
                << spawn.position.x << "," << spawn.position.y << " does not exist.\n";
            report.skippedSpawns++;
            continue;
        }

        cell& targetCell = grid.gridmap.at(spawn.position);

        if (!targetCell.walkable)
        {
            std::cout << "Skipping spawn '" << spawn.spawnId << "': grid cell "
                << spawn.position.x << "," << spawn.position.y << " is not walkable.\n";
            report.skippedSpawns++;
            continue;
        }

        if (targetCell.occupied)
        {
            std::cout << "Skipping spawn '" << spawn.spawnId << "': grid cell "
                << spawn.position.x << "," << spawn.position.y << " is already occupied.\n";
            report.skippedSpawns++;
            continue;
        }

        try
        {
            UnitBase unit = unitFactory.BuildUnit(spawn.unitId);
            unit.team = spawn.teamOverride;
            activeUnits.push_back(CombatUnit{spawn.spawnId, unit, spawn.position});
            targetCell.occupied = true;
            report.spawnedUnits++;
        }
        catch (const std::exception& exception)
        {
            std::cout << "Skipping spawn '" << spawn.spawnId << "': "
                << exception.what() << "\n";
            report.skippedSpawns++;
        }
    }

    return report;
}

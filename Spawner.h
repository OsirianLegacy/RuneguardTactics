#pragma once

#include "Data/CombatStructs.h"
#include "GridLogic.h"
#include "Data/MissionStructs.h"
#include "TiledMap.h"
#include "Units/UnitFactory.h"

#include <vector>

class Spawner
{
public:
    explicit Spawner(UnitFactory& unitFactory);

    SpawnReport spawnEncounter(
        const EncounterData& encounter,
        const TiledMap& map,
        GridLogic& grid,
        std::vector<CombatUnit>& activeUnits) const;

private:
    UnitFactory& unitFactory;
};

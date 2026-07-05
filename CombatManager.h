#pragma once

#include "CombatStructs.h"
#include "GridLogic.h"
#include "MissionStructs.h"
#include "Spawner.h"
#include "TiledMap.h"
#include "Units/UnitFactory.h"

#include <filesystem>
#include <string>
#include <vector>

class CombatManager
{
public:
    explicit CombatManager(
        GridLogic& grid,
        std::filesystem::path unitDatabaseDirectory = "Units/UnitDatabase");

    bool startMissionEncounter(const MissionData& mission, const std::string& encounterId);
    void update(float deltaTime);

    [[nodiscard]] const std::vector<CombatUnit>& getActiveUnits() const;
    [[nodiscard]] const std::vector<DeploymentSlot>& getPlayerDeploymentSlots() const;
    [[nodiscard]] TiledMap& getCurrentMap();
    [[nodiscard]] const TiledMap& getCurrentMap() const;
    [[nodiscard]] const CombatState& getCombatState() const;

private:
    const EncounterData* findEncounter(const MissionData& mission, const std::string& encounterId) const;

    UnitFactory unitFactory;
    Spawner spawner;
    TiledMap currentMap;
    GridLogic* grid = nullptr;
    CombatState combatState;
};

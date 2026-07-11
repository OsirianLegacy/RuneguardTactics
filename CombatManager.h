#pragma once

#include "Data/CombatStructs.h"
#include "GridLogic.h"
#include "Data/MissionStructs.h"
#include "Spawner.h"
#include "TiledMap.h"
#include "Units/UnitFactory.h"
#include "GameState.h"
#include <filesystem>
#include <string>
#include <vector>

class CombatManager
{
public:
    // When we construct the CombatManager pass through GridLogic and the UnitDatabase path.
    explicit CombatManager(
        GridLogic& grid,
        std::filesystem::path unitDatabaseDirectory = "Units/UnitDatabase");
    // Starts the Mission Encounter, see .cpp comment for more detail.
    bool startMissionEncounter(const MissionData& mission, const std::string& encounterId);
    // primarily used to update combat units animations retrieved from their spritesheet.
    void update(float deltaTime);
    // The active units in Combat.
    [[nodiscard]] const std::vector<CombatUnit>& getActiveUnits() const;
    // The Deployment slots that CombatManager gets from TiledMap.
    [[nodiscard]] const std::vector<DeploymentSlot>& getPlayerDeploymentSlots() const;
    // used to retrieve the current TiledMap data. Mutable, so be careful with it.
    [[nodiscard]] TiledMap& getCurrentMap();
    // used to retrieve the current TiledMap data. Safe and preferred getter unless data needs to be changed.
    [[nodiscard]] const TiledMap& getCurrentMap() const;
    // used to retrieve the Combat State from the CombatManager, Safe.
    [[nodiscard]] const CombatState& getCombatState() const;
    void setGameState(gamestate newGameState);
    void setGameEvent(gameevent newGameEvent);
private:

    const EncounterData* findEncounter(const MissionData& mission, const std::string& encounterId) const;
    gamestate gameState;
    UnitFactory unitFactory;
    Spawner spawner;
    TiledMap currentMap;
    GridLogic* grid = nullptr;
    CombatState combatState;
    gameevent currentGameEvent = gameevent::null;
};

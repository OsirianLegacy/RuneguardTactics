#pragma once

#include "MissionStructs.h"
#include "Units/UnitBase.h"

#include <string>
#include <vector>

enum class UnitAnimationState
{
    Idle,
    Damaged,
    Healed,
    Highlighted
};

struct CombatUnit
{
    std::string spawnId;
    UnitBase unit;
    coord position;
    UnitAnimationState animationState = UnitAnimationState::Idle;
    int animationFrame = 0;
    float animationTimer = 0.0f;
    float animationFramesPerSecond = 6.0f;
};

struct CombatState
{
    EncounterData encounter;
    std::vector<DeploymentSlot> playerDeploymentSlots;
    std::vector<CombatUnit> activeUnits;
};

struct SpawnReport
{
    int requestedSpawns = 0;
    int spawnedUnits = 0;
    int skippedSpawns = 0;
};

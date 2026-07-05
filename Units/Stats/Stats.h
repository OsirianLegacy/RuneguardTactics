#pragma once
#include "AP.h"
#include "damage.h"
#include "Defense.h"
#include "Healing.h"
#include "Health.h"
#include "Movement.h"
#include "Range.h"
#include "speed.h"
#include "UnitDefinition.h"

struct stats
{
    health health;
    Defense defense;
    damage damage;
    Healing healing;
    Movement movement; 
    Range range;
    speed speed;
    ap ap; 
    
    stats(const UnitDefinition& def)
    : health(def.health),
      defense(def.defense),
      damage(def.damage),
      healing(def.healing),
      movement(def.movement),
      range(def.range),
      speed(def.speed),
      ap(2)
    {
    }
};

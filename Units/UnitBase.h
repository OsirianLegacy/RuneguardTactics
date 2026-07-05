#pragma once
#include <string>
#include "Stats/UnitDefinition.h"
#include "Stats/Stats.h"
#include <iostream>

class UnitBase
{
public:
  std::string UnitID;
  std::string UnitName;
  TEAM team;
  MOVETYPE movetype;
  stats stats;
  bool isAI;

  UnitBase(UnitDefinition def)
    : UnitID(def.UnitID), UnitName(def.UnitName), team(def.team), movetype(def.movetype), stats(def), isAI(def.isAI)
  {}
  void debug_unit();
};

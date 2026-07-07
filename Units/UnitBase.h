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
  UnitSpriteSheet spriteSheet;
  stats stats;
  bool isAI;

  UnitBase(UnitDefinition def)
    : UnitID(def.UnitID),
      UnitName(def.UnitName),
      team(def.team),
      movetype(def.movetype),
      spriteSheet(def.spriteSheet),
      stats(def),
      isAI(def.isAI)
  {}
  // debugging functions
  void debug_unit();
  // getter functions
  struct stats getStats() const;
  std::string getID() const;
  std::string getName() const;
  TEAM getTeam() const;
  MOVETYPE getMovetype() const;
  UnitSpriteSheet getSpriteSheet() const;
  bool getIsAI() const;
};

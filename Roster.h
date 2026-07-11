//
// Created by Jkurt on 7/6/2026.
//

#ifndef RUNEGUARDTACTICS_ROSTER_H
#define RUNEGUARDTACTICS_ROSTER_H
#include "Data/CombatStructs.h"
#include <vector>
class Roster {
private:
    std::vector<CombatUnit> roster;

public:
CombatUnit getCombatUnit(CombatUnit combatUnit);
           addUnitToRoster(CombatUnit combatUnit);
           removeUnitFromRoster(CombatUnit combatUnit);
};




#endif //RUNEGUARDTACTICS_ROSTER_H
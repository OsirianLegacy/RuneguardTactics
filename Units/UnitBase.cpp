#include "UnitBase.h"
#include <iostream>
void UnitBase::debug_unit()
{
    std::cout << "UnitBase with ID: " << this->UnitID << " was created by the Factory. " << std::endl 
    << "Debugging Stats: " << std::endl 
    << "health: " << this->stats.health.getcurrenthealth() << std::endl 
    << "Defense: " << this->stats.defense.get_current() << std::endl
    << "Damage: " << this->stats.damage.get_current() << std::endl
    << "Healing: " << this->stats.healing.get_current() << std::endl
    << "Movement: " << this->stats.movement.get_current() << std::endl
    << "Range: " << this->stats.range.get_current() << std::endl
    << "Speed: " << this->stats.speed.get_current() << std::endl
    << "AP: " << this->stats.ap.get_current() << std::endl << std::endl;
};


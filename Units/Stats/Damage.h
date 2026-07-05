#pragma once
#include "UnitDefinition.h"

struct damage
{
    // variables
    int current;
    int base;
    int modifier;
    
    // constructor
    damage(int base)
    {
        this->current = base;
        this->base = base;
        this->modifier = 0;
    }
    
    int get_current();
    // functions
    // sets current damage from base+modifier
    // void setdamage();
    
    // increases the base damage of a unit.
    //void increase_base(int amount);
    
    // decreases the base damage of a unit.
    //void decrease_base(int amount);
    
    // increases the modifier applied to current damage value.
    //void increase_modifier(int amount);
    
    // decreases the modifier applied to current damage value.
    //void decrease_modifier(int amount);
 
    
};

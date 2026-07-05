#pragma once
#include "UnitDefinition.h"
struct health
{
private:
    // variables
    int current;
    int base;
    int max;
    int modifier;
    
    // constructor
public:
    health(int base)
    {
        this->base = base;
        this->max = base;
        this->current = this->max;
        this->modifier = 0;
    }
    
    // fucntions
    int takedamage(int amount);
    int heal(int amount);
    int getcurrenthealth();
};

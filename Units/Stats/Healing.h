#pragma once

struct Healing
{
    // variables
    int current;
    int base;
    int modifier;
    
    // constructor
    Healing(int base)
    {
        this->base = base;
        this->current = base;
        this->modifier = 0;
    }
    
    // functions
    int get_current();
};

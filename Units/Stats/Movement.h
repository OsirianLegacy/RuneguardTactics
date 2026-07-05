#pragma once

struct Movement
{
    int current;
    int base;
    int modifier;
    
    Movement(int base)
    {
        this->base = base;
        this->current = base;
        this->modifier = 0;
    }
    
    // functions
    int get_current();
};

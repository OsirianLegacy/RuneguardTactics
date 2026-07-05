#pragma once

struct speed
{
    int current;
    int base;
    int modifier;
    
    speed(int base)
    {
        this->base = base;
        this->current = base;
        this->modifier = 0;
    }
    
    // functions
    int get_current();
};

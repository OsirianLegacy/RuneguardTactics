#pragma once

struct ap
{
    // variables
    int current;
    int base;
    int max;
    int modifier;
    
    // constructor
    ap(int base)
    {
        this->current = base;
        this->base = base;
        this->max = base;
        this->modifier = 0;
    }
    
    // functions
    int spend(int amount);
    int gain(int amount);
    int set_max(int amount);
    int lower_mod(int amount);
    int raise_mod(int amount);
    int get_current();
};


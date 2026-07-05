#pragma once

struct Range
{
    int current;
    int base;
    int modifier;
    
    Range(int base)
    {
        this->base = base;
        this->current = base;
        this->modifier = 0;
    }
    
    int get_current();
};

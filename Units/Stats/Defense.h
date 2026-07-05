#pragma once
#include <iostream>

struct Defense
{
    // variables
    int current;
    int base;
    int modifier;

    // constructor
    Defense(int base)
    {
        this->current = base;
        this->base = base;
        this->modifier = 0;
    }
    
    // functions
    int reducedamage(int amount);
    int setcurrent(int new_defense);
    int increasemodifier(int amount);
    int decreasemodifier(int amount);
    int increasebase(int amount);
    int decreasebase(int amount);
    int recalculatecurrent();
    int get_current();
};

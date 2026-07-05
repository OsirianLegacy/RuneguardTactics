#include "AP.h"
#include <iostream>
#include <algorithm>
int ap::spend(int amount)
{
    if (amount <= current)
    {
        current -= amount;    
        return current;
    }
    std::cout << "Passed amount value: " << amount << " is greater than current value: " << current << " Unit cannot afford spend request." << std::endl;
    return current;
}

int ap::gain(int amount)
{
    current = std::min(current + amount, max);
    return current;
}

int ap::lower_mod(int amount)
{
    modifier -= amount;
    return modifier;
}

int ap::raise_mod(int amount)
{
    modifier += amount;
    return modifier;
}

int ap::set_max(int amount)
{
    max = amount;
    return max;
}

int ap::get_current()
{
    return this->current;
}



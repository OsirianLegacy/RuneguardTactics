#include "Defense.h"
#include <algorithm>
#include <iostream>
int Defense::reducedamage(int amount)
{
    int new_amount = amount -= std::max(amount - this->current, 0);
    std::cout << "Unit's Defense of: " << this->current << "reduced incoming damage of: " << amount << "to: " << new_amount << std::endl;
    return new_amount;
};

int Defense::increasebase(int amount)
{
    int new_amount = amount += this->base;
    std::cout << "Unit's Base Defense Score has increased by: " << amount << ". New Base Defense Score: " << new_amount << std::endl;
    return new_amount;
}

int Defense::decreasebase(int amount)
{
    int new_amount = amount -= this->base;
    std::cout << "Unit's Base Defense Score has decreased by: " << amount << ". New Base Defense Score: " << new_amount << std::endl;
    return new_amount;
}

int Defense::decreasemodifier(int amount)
{
    int new_amount = amount -= this->modifier;
    std::cout << "Unit's Defense Modifier has decreased by: " << amount <<  ". New Defense Modifier: " << new_amount << std::endl;
    return new_amount;
}

int Defense::increasemodifier(int amount)
{
    int new_amount = amount += this->modifier;
    std::cout << "Unit's Defense Modifier has increased by: " << amount << ". New Defense Modifier: " << new_amount << std::endl;
    return new_amount;
}

int Defense::setcurrent(int new_defense)
{
    current = new_defense;
    return new_defense;
}

int Defense::recalculatecurrent()
{
    current = this->base + this->modifier - this->current;
    return current;
}

int Defense::get_current()
{
    return this->current;
}

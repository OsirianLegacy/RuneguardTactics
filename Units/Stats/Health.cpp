#include "Health.h"
#include <algorithm>
int health::takedamage(int amount)
{
    current = std::clamp(current - amount, 0, this->max);
    return current;
}

int health::heal(int amount)
{
    current = std::clamp(current + amount, 0, this->max);
    return current;
}

int health::getcurrenthealth()
{
    return this->current;
}

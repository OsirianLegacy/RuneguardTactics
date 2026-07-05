#pragma once
#include <string>

enum TEAM
{
    PLAYER,
    ENEMY,
    CIVILIAN,
    NEUTRAL,
};

enum MOVETYPE
{
    CARDINAL,
    DIAGONAL,
    TELEPORT,
};

struct UnitDefinition
{
    std::string UnitID;
    std::string UnitName;
    TEAM team;
    MOVETYPE movetype;
    int health;
    int defense;
    int damage;
    int healing;
    int movement;
    int range;
    int speed;
    bool isAI;
    
    UnitDefinition(std::string UnitID, std::string UnitName, TEAM team, MOVETYPE movetype,
                    int health, int defense, int damage, int healing, int movement, int range, int speed, bool isAI)
    {
        this->UnitID = UnitID;
        this->UnitName = UnitName;
        this->team = team;
        this->movetype = movetype;
        this->health = health;
        this->defense = defense;
        this->damage = damage;
        this->healing = healing;
        this->movement = movement;
        this->range = range;
        this->speed = speed;
        this->isAI = isAI;
    }
};

#pragma once
#include <string>
#include <array>
#include <raylib.h>

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

struct UnitSpriteSheet
{
    Texture2D texture = {};
    int frameWidth = 0;
    int frameHeight = 0;
    std::array<Rectangle, 4> idleFrames = {};
    std::array<Rectangle, 4> damagedFrames = {};
    std::array<Rectangle, 4> healedFrames = {};
    std::array<Rectangle, 4> highlightedFrames = {};
};

struct UnitDefinition
{
    std::string UnitID;
    std::string UnitName;
    TEAM team;
    MOVETYPE movetype;
    UnitSpriteSheet spriteSheet;
    int health;
    int defense;
    int damage;
    int healing;
    int movement;
    int range;
    int speed;
    bool isAI;
    
    UnitDefinition(
        const std::string &UnitID,
        const std::string &UnitName,
        const TEAM team,
        const MOVETYPE movetype,
        UnitSpriteSheet spriteSheet,
        const int health,
        const int defense,
        const int damage,
        const int healing,
        const int movement,
        const int range,
        const int speed,
        const bool isAI)
    {
        this->UnitID = UnitID;
        this->UnitName = UnitName;
        this->team = team;
        this->movetype = movetype;
        this->spriteSheet = spriteSheet;
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

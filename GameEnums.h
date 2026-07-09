//
// Created by Jkurt on 7/6/2026.
//
#ifndef RUNEGUARDTACTICS_GAMEENUMS_H
#define RUNEGUARDTACTICS_GAMEENUMS_H

#include <string>

enum class gamestate
{
    mainmenu,
    newgameunitselector,
    city,
    roster,
    tavern,
    clinic,
    missionboard,
    combat,
    missionreport
};

inline std::string toString(gamestate state)
{
    switch (state)
    {
        case gamestate::mainmenu:
            return "mainmenu";
        case gamestate::newgameunitselector:
            return "newgameunitselector";
        case gamestate::city:
            return "city";
        case gamestate::roster:
            return "roster";
        case gamestate::tavern:
            return "tavern";
        case gamestate::clinic:
            return "clinic";
        case gamestate::missionboard:
            return "missionboard";
        case gamestate::combat:
            return "combat";
        case gamestate::missionreport:
            return "missionreport";
    }

    return "unknown";
}

enum class missionoutcome
{
    success,
    failure
};

inline std::string toString(missionoutcome outcome)
{
    switch (outcome)
    {
        case missionoutcome::success:
            return "success";
        case missionoutcome::failure:
            return "failure";
    }

    return "unknown";
}

enum class gameevent
{
    newgame,
    continuegame,
    exitgame,
    loadsavegame,
    deletesavegame,
    openroster,
    opentavern,
    openclinic,
    openmissionboard,
    openmainmenu,
    opencity,
    closeactivemenu,
    null
};

inline std::string toString(gameevent event)
{
    switch (event)
    {
        case gameevent::newgame:
            return "newgame";
        case gameevent::continuegame:
            return "continuegame";
        case gameevent::exitgame:
            return "exitgame";
        case gameevent::loadsavegame:
            return "loadsavegame";
        case gameevent::deletesavegame:
            return "deletesavegame";
        case gameevent::openroster:
            return "openroster";
        case gameevent::opentavern:
            return "opentavern";
        case gameevent::openclinic:
            return "openclinic";
        case gameevent::openmissionboard:
            return "openmissionboard";
        case gameevent::openmainmenu:
            return "openmainmenu";
        case gameevent::opencity:
            return "opencity";
        case gameevent::closeactivemenu:
            return "closeactivemenu";
        case gameevent::null:
            return "null";
    }

    return "unknown";
}
#endif //RUNEGUARDTACTICS_GAMEENUMS_H

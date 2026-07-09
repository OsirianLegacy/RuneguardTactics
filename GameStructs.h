//
// Created by Jkurt on 7/6/2026.
//

#ifndef RUNEGUARDTACTICS_GAMESTRUCTS_H
#define RUNEGUARDTACTICS_GAMESTRUCTS_H
#include "CombatStructs.h"
#include "GameEnums.h"
#include <vector>
#include <map>
#include <string>
#include <cstdint>

struct UserSettingsData
{
    float masterVolume = 1.0f;
    int resolutionWidth = 1600;
    int resolutionHeight = 900;
    bool fullscreen = false;
};

// GameData stores everything that would need to be loaded on a Save being loaded. Also the values the Save Manager cares about.
struct GameData
{
    int playerGold = 0;
    // holds the player's roster of units
    std::vector<CombatUnit> roster;
    // the mission deck is where all currently available missions for the Mission Manager to pull from
    std::vector<MissionData> missionDeck;
    // map of missionId to missionOutcome (success/failure) for the Mission Manager to pull from to create Mission Deck.
    std::map<std::string, missionoutcome> missionReports;
    // the current mission the player is on. Can be null if they're not currently in Combat.
    const MissionData* currentMission = nullptr;
    // the current game state. Primarily controls things like UI.
    gamestate gameState = gamestate::mainmenu;
    // TODO: Add Items to the game and store them in GameData.
    UserSettingsData userSettings;
};





#endif //RUNEGUARDTACTICS_GAMESTRUCTS_H

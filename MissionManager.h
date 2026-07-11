//
// Created by Jkurt on 7/7/2026.
//

#ifndef RUNEGUARDTACTICS_MISSIONMANAGER_H
#define RUNEGUARDTACTICS_MISSIONMANAGER_H
#include "Data/GameEnums.h"

class MissionManager {
public:
    void setGameState(gamestate newGameState);

    void setGameEvent(gameevent newGameEvent);

private:
    gamestate gameState = gamestate::mainmenu;
    gameevent currentGameEvent = gameevent::null;
};


#endif //RUNEGUARDTACTICS_MISSIONMANAGER_H
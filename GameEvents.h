//
// Created by Jkurt on 7/7/2026.
//

#ifndef RUNEGUARDTACTICS_GAMEEVENTS_H
#define RUNEGUARDTACTICS_GAMEEVENTS_H
#include "CombatManager.h"
#include "InputManager.h"
#include "GameUI.h"
#include "MissionManager.h"
#include "GameState.h"
class GameEvents {
public:
    void updateState() const;

    void checkGameEvent(gameevent newGameEvent);
    void sendGameEvent(gameevent newGameEvent) const;
    GameEvents(CombatManager &incombatManager, GameState &ingameState, InputManager &ininputManager, GameUI &ingameUI,
               MissionManager &inmissionManager);

    void checkGameState(gamestate newGameState);
    gameevent currentGameEvent = gameevent::null;
private:
    CombatManager& combatManager;
    GameState& gameState;
    InputManager& inputManager;
    GameUI& gameUI;
    MissionManager& missionManager;
    gamestate currentGameState = gamestate::mainmenu;

};


#endif //RUNEGUARDTACTICS_GAMEEVENTS_H
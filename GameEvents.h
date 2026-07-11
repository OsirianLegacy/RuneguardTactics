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
#include "Missions.h"
#include "Renderer.h"

class GridVisuals;

class GameEvents {
public:
    void updateState() const;

    void checkGameEvent(gameevent newGameEvent);
    void sendGameEvent(gameevent newGameEvent) const;
    GameEvents(CombatManager &incombatManager, GameState &ingameState, InputManager &ininputManager, GameUI &ingameUI,
               MissionManager &inmissionManager, MissionDatabase &inmissionDatabase, Renderer &inrenderer,
               GridVisuals &ingridVisuals);

    void checkGameState(gamestate newGameState);
    gameevent currentGameEvent = gameevent::null;
private:
    bool startTestCombat() const;
    void setResolution1080p() const;
    void toggleFullscreen() const;
    void applyDisplaySettings() const;

    CombatManager& combatManager;
    GameState& gameState;
    InputManager& inputManager;
    GameUI& gameUI;
    MissionManager& missionManager;
    MissionDatabase& missionDatabase;
    Renderer& renderer;
    GridVisuals& gridVisuals;
    gamestate currentGameState = gamestate::mainmenu;

};


#endif //RUNEGUARDTACTICS_GAMEEVENTS_H

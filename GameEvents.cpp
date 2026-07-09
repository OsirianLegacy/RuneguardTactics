//
// Created by Jkurt on 7/7/2026.
//

#include "GameEvents.h"
#include "GameState.h"
#include "iostream"
void GameEvents::updateState() const
{
    combatManager.setGameState(currentGameState);
    inputManager.setGameState(currentGameState);
    gameUI.setGameState(currentGameState);
    missionManager.setGameState(currentGameState);
    std::cout << "GameEvents sending New Game State" << toString(currentGameState) << "\n";
}

void GameEvents::checkGameEvent(const gameevent newGameEvent)
{
    if (newGameEvent == gameevent::null)
    {
        return;
    }

    if (newGameEvent != currentGameEvent) {
        currentGameEvent = newGameEvent;
        std::cout << "Event System received new game event: " << toString(currentGameEvent) << "\n";
        sendGameEvent(currentGameEvent);
    }
}

void GameEvents::sendGameEvent(const gameevent newGameEvent) const
{
    std::cout << "Event System sending new Event to systems\n";
    combatManager.setGameEvent(currentGameEvent);
    inputManager.setGameEvent(currentGameEvent);
    gameUI.setGameEvent(currentGameEvent);
    gameState.setGameEvent(currentGameEvent);
    missionManager.setGameEvent(currentGameEvent);
}

GameEvents::GameEvents(
    CombatManager& incombatManager,
    GameState& ingameState,
    InputManager& ininputManager,
    GameUI& ingameUI,
    MissionManager& inmissionManager)
    : combatManager(incombatManager),
      gameState(ingameState),
      inputManager(ininputManager),
      gameUI(ingameUI),
      missionManager(inmissionManager)
{
}

void GameEvents::checkGameState(gamestate newGameState)
{
    if (newGameState != currentGameState) {
        currentGameState = newGameState;
        updateState();
    }
}


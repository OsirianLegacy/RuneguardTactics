//
// Created by Jkurt on 7/7/2026.
//

#include "MissionManager.h"

#include <iostream>

void MissionManager::setGameState(gamestate newGameState) {
    gameState = newGameState;
}

void MissionManager::setGameEvent(gameevent newGameEvent)
{
    if (newGameEvent != currentGameEvent)
    {
        currentGameEvent = newGameEvent;
        std::cout << "Mission Manager received new game event: " << toString(currentGameEvent) << "\n";
    }
}

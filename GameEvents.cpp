//
// Created by Jkurt on 7/7/2026.
//

#include "GameEvents.h"
#include "GameState.h"
#include "GridVisuals.h"
#include "iostream"
#include <raylib.h>

namespace
{
    constexpr const char* TestMissionId = "dusk_ferrets";
    constexpr const char* TestEncounterId = "dusk_ferrets_hideout_entrance";
    constexpr int Resolution1080pWidth = 1920;
    constexpr int Resolution1080pHeight = 1080;
}

void GameEvents::updateState() const
{
    combatManager.setGameState(currentGameState);
    inputManager.setGameState(currentGameState);
    gameUI.setGameState(currentGameState);
    missionManager.setGameState(currentGameState);
    gridVisuals.setState(currentGameState);
    std::cout << "GameEvents sending New Game State" << toString(currentGameState) << "\n";
}

void GameEvents::checkGameEvent(const gameevent newGameEvent)
{
    if (newGameEvent == gameevent::null)
    {
        return;
    }

    currentGameEvent = newGameEvent;
    std::cout << "Event System received new game event: " << toString(currentGameEvent) << "\n";
    sendGameEvent(currentGameEvent);
    gameUI.setGameEvent(gameevent::null);
    currentGameEvent = gameevent::null;
}

void GameEvents::sendGameEvent(const gameevent newGameEvent) const
{
    std::cout << "Event System sending new Event to systems\n";

    if (newGameEvent == gameevent::setresolution1080p)
    {
        setResolution1080p();
        return;
    }

    if (newGameEvent == gameevent::togglefullscreen)
    {
        toggleFullscreen();
        return;
    }

    if (newGameEvent == gameevent::starttestcombat && !startTestCombat())
    {
        return;
    }

    combatManager.setGameEvent(newGameEvent);
    inputManager.setGameEvent(newGameEvent);
    gameState.setGameEvent(newGameEvent);
    missionManager.setGameEvent(newGameEvent);
}

GameEvents::GameEvents(
    CombatManager& incombatManager,
    GameState& ingameState,
    InputManager& ininputManager,
    GameUI& ingameUI,
    MissionManager& inmissionManager,
    MissionDatabase& inmissionDatabase,
    Renderer& inrenderer,
    GridVisuals& ingridVisuals)
    : combatManager(incombatManager),
      gameState(ingameState),
      inputManager(ininputManager),
      gameUI(ingameUI),
      missionManager(inmissionManager),
      missionDatabase(inmissionDatabase),
      renderer(inrenderer),
      gridVisuals(ingridVisuals)
{
}

bool GameEvents::startTestCombat() const
{
    const MissionData* mission = missionDatabase.findMission(TestMissionId);

    if (mission == nullptr)
    {
        std::cout << "Failed to start test combat: mission '" << TestMissionId << "' was not found.\n";
        return false;
    }

    if (!combatManager.startMissionEncounter(*mission, TestEncounterId))
    {
        std::cout << "Failed to start test combat encounter '" << TestEncounterId << "'.\n";
        return false;
    }

    gameState.setCurrentMission(mission);
    renderer.setTileMap(&combatManager.getCurrentMap());
    renderer.setActiveUnits(&combatManager.getActiveUnits());
    return true;
}

void GameEvents::setResolution1080p() const
{
    gameState.setResolutionWidth(Resolution1080pWidth);
    gameState.setResolutionHeight(Resolution1080pHeight);
    applyDisplaySettings();
    std::cout << "Resolution set to 1920x1080\n";
}

void GameEvents::toggleFullscreen() const
{
    gameState.setFullscreen(!gameState.isFullscreen());
    applyDisplaySettings();
    std::cout << "Fullscreen set to " << (gameState.isFullscreen() ? "true" : "false") << "\n";
}

void GameEvents::applyDisplaySettings() const
{
    const int width = gameState.getResolutionWidth();
    const int height = gameState.getResolutionHeight();
    const bool shouldFullscreen = gameState.isFullscreen();
    int renderWidth = width;
    int renderHeight = height;

    if (shouldFullscreen)
    {
        const int currentMonitor = GetCurrentMonitor();
        const int monitorWidth = GetMonitorWidth(currentMonitor);
        const int monitorHeight = GetMonitorHeight(currentMonitor);
        renderWidth = monitorWidth;
        renderHeight = monitorHeight;

        if (!IsWindowFullscreen())
        {
            SetWindowSize(monitorWidth, monitorHeight);
            ToggleFullscreen();
        }
    }
    else if (!shouldFullscreen && IsWindowFullscreen())
    {
        ToggleFullscreen();
        SetWindowSize(width, height);
    }
    else if (!shouldFullscreen)
    {
        SetWindowSize(width, height);
    }

    renderer.width = renderWidth;
    renderer.height = renderHeight;
    gridVisuals.screenWidth = renderWidth;
    gridVisuals.screenHeight = renderHeight;
}

void GameEvents::checkGameState(gamestate newGameState)
{
    if (newGameState != currentGameState) {
        currentGameState = newGameState;
        updateState();
    }
}


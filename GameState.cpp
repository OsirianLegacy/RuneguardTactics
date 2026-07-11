//
// Created by Jkurt on 7/6/2026.
//

#include "GameState.h"

const GameData& GameState::getGameData() const
{
    return gameData;
}

void GameState::setGameData(const GameData& gameData)
{
    this->gameData = gameData;
}

int GameState::getPlayerGold() const
{
    return gameData.playerGold;
}

void GameState::setPlayerGold(const int playerGold)
{
    gameData.playerGold = playerGold;
}

const std::vector<CombatUnit>& GameState::getRoster() const
{
    return gameData.roster;
}

void GameState::setRoster(const std::vector<CombatUnit>& roster)
{
    gameData.roster = roster;
}

const std::vector<MissionData>& GameState::getMissionDeck() const
{
    return gameData.missionDeck;
}

void GameState::setMissionDeck(const std::vector<MissionData>& missionDeck)
{
    gameData.missionDeck = missionDeck;
}

const std::map<std::string, missionoutcome>& GameState::getMissionReports() const
{
    return gameData.missionReports;
}

void GameState::setMissionReports(const std::map<std::string, missionoutcome>& missionReports)
{
    gameData.missionReports = missionReports;
}

const MissionData* GameState::getCurrentMission() const
{
    return gameData.currentMission;
}

void GameState::setCurrentMission(const MissionData* currentMission)
{
    gameData.currentMission = currentMission;
}

gamestate GameState::getGameState() const
{
    return gameData.gameState;
}

void GameState::setGameState(const gamestate gameState)
{
    gameData.gameState = gameState;
}

const UserSettingsData& GameState::getUserSettings() const
{
    return gameData.userSettings;
}

void GameState::setUserSettings(const UserSettingsData& userSettings)
{
    gameData.userSettings = userSettings;
}

float GameState::getMasterVolume() const
{
    return gameData.userSettings.masterVolume;
}

void GameState::setMasterVolume(const float masterVolume)
{
    gameData.userSettings.masterVolume = masterVolume;
}

int GameState::getResolutionWidth() const
{
    return gameData.userSettings.resolutionWidth;
}

void GameState::setResolutionWidth(const int resolutionWidth)
{
    gameData.userSettings.resolutionWidth = resolutionWidth;
}

int GameState::getResolutionHeight() const
{
    return gameData.userSettings.resolutionHeight;
}

void GameState::setResolutionHeight(const int resolutionHeight)
{
    gameData.userSettings.resolutionHeight = resolutionHeight;
}

bool GameState::isFullscreen() const
{
    return gameData.userSettings.fullscreen;
}

void GameState::setFullscreen(const bool fullscreen)
{
    gameData.userSettings.fullscreen = fullscreen;
}

void GameState::setGameEvent(gameevent newGameEvent)
{
    if (currentGameEvent != newGameEvent)
    {
        currentGameEvent = newGameEvent;
        std::cout << "Game State received new game event: " << toString(currentGameEvent) << "\n";

        if (currentGameEvent == gameevent::newgame)
        {
            setGameState(gamestate::newgameunitselector);
        }

        if (currentGameEvent == gameevent::starttestcombat)
        {
            setGameState(gamestate::combat);
        }
    }
}

GameState::GameState() {

}




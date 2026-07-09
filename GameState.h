//
// Created by Jkurt on 7/6/2026.
//

#ifndef RUNEGUARDTACTICS_GAMESTATE_H
#define RUNEGUARDTACTICS_GAMESTATE_H

#include "GameStructs.h"
class GameState {
public:
    GameState();

    void setGameEvent(gameevent newGameEvent);

    [[nodiscard]] const GameData& getGameData() const;
    void setGameData(const GameData& gameData);

    [[nodiscard]] int getPlayerGold() const;
    void setPlayerGold(int playerGold);

    [[nodiscard]] const std::vector<CombatUnit>& getRoster() const;
    void setRoster(const std::vector<CombatUnit>& roster);

    [[nodiscard]] const std::vector<MissionData>& getMissionDeck() const;
    void setMissionDeck(const std::vector<MissionData>& missionDeck);

    [[nodiscard]] const std::map<std::string, missionoutcome>& getMissionReports() const;
    void setMissionReports(const std::map<std::string, missionoutcome>& missionReports);

    [[nodiscard]] const MissionData* getCurrentMission() const;
    void setCurrentMission(const MissionData* currentMission);

    [[nodiscard]] gamestate getGameState() const;
    void setGameState(gamestate gameState);

    [[nodiscard]] const UserSettingsData& getUserSettings() const;
    void setUserSettings(const UserSettingsData& userSettings);

    [[nodiscard]] float getMasterVolume() const;
    void setMasterVolume(float masterVolume);

    [[nodiscard]] int getResolutionWidth() const;
    void setResolutionWidth(int resolutionWidth);

    [[nodiscard]] int getResolutionHeight() const;
    void setResolutionHeight(int resolutionHeight);

    [[nodiscard]] bool isFullscreen() const;
    void setFullscreen(bool fullscreen);

private:
    GameData gameData;
    gameevent currentGameEvent = gameevent::null;
};


#endif //RUNEGUARDTACTICS_GAMESTATE_H

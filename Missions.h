//
// Created by Jkurt on 7/6/2026.
//

#ifndef RUNEGUARDTACTICS_MISSIONS_H
#define RUNEGUARDTACTICS_MISSIONS_H

#include "Data/MissionStructs.h"

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>
// stored in Missions.h, holds all missions in the game.
class MissionDatabase
{
public:
    bool loadFromDirectories(
        const std::filesystem::path& missionsDirectory,
        const std::filesystem::path& encountersDirectory);

    [[nodiscard]] const MissionData* findMission(const std::string& missionId) const;
    [[nodiscard]] const EncounterData* findEncounter(const std::string& encounterId) const;
    [[nodiscard]] const std::vector<MissionData>& getMissions() const;

private:
    std::vector<MissionData> missions;
    std::unordered_map<std::string, EncounterData> encountersById;
};

#endif //RUNEGUARDTACTICS_MISSIONS_H

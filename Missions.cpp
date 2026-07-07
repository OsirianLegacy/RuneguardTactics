#include "Missions.h"

#include <fstream>
#include <iostream>
#include <set>

#include <nlohmann/json.hpp>

namespace
{
    using json = nlohmann::json;

    bool hasJsonExtension(const std::filesystem::path& filePath)
    {
        return filePath.extension() == ".json";
    }

    bool readJsonFile(const std::filesystem::path& filePath, json& outJson)
    {
        std::ifstream file(filePath);

        if (!file)
        {
            std::cout << "Failed to open JSON file: " << filePath.string() << "\n";
            return false;
        }

        try
        {
            file >> outJson;
        }
        catch (const json::exception& exception)
        {
            std::cout << "Failed to parse JSON file '" << filePath.string()
                << "': " << exception.what() << "\n";
            return false;
        }

        return true;
    }

    bool requireObject(
        const json& parent,
        const char* key,
        const std::filesystem::path& filePath,
        const json*& outObject)
    {
        if (!parent.contains(key) || !parent.at(key).is_object())
        {
            std::cout << "JSON file '" << filePath.string()
                << "' is missing required object field '" << key << "'.\n";
            return false;
        }

        outObject = &parent.at(key);
        return true;
    }

    bool requireString(
        const json& parent,
        const char* key,
        const std::filesystem::path& filePath,
        std::string& outValue)
    {
        if (!parent.contains(key) || !parent.at(key).is_string())
        {
            std::cout << "JSON file '" << filePath.string()
                << "' is missing required string field '" << key << "'.\n";
            return false;
        }

        outValue = parent.at(key).get<std::string>();

        if (outValue.empty())
        {
            std::cout << "JSON file '" << filePath.string()
                << "' has empty required string field '" << key << "'.\n";
            return false;
        }

        return true;
    }

    bool requireStringArray(
        const json& parent,
        const char* key,
        const std::filesystem::path& filePath,
        std::vector<std::string>& outValues)
    {
        if (!parent.contains(key) || !parent.at(key).is_array())
        {
            std::cout << "JSON file '" << filePath.string()
                << "' is missing required array field '" << key << "'.\n";
            return false;
        }

        outValues.clear();

        for (const json& value : parent.at(key))
        {
            if (!value.is_string())
            {
                std::cout << "JSON file '" << filePath.string()
                    << "' has a non-string entry in array field '" << key << "'.\n";
                return false;
            }

            const std::string id = value.get<std::string>();

            if (id.empty())
            {
                std::cout << "JSON file '" << filePath.string()
                    << "' has an empty string entry in array field '" << key << "'.\n";
                return false;
            }

            outValues.push_back(id);
        }

        if (outValues.empty())
        {
            std::cout << "JSON file '" << filePath.string()
                << "' must list at least one entry in array field '" << key << "'.\n";
            return false;
        }

        return true;
    }

    bool collectObjectEntries(
        const json& root,
        const char* collectionKey,
        const char* contentType,
        const std::filesystem::path& filePath,
        std::vector<const json*>& outEntries)
    {
        outEntries.clear();

        if (root.is_array())
        {
            for (const json& entry : root)
            {
                if (!entry.is_object())
                {
                    std::cout << contentType << " JSON file '" << filePath.string()
                        << "' has a non-object entry in its root array.\n";
                    return false;
                }

                outEntries.push_back(&entry);
            }
        }
        else if (root.is_object())
        {
            if (root.contains(collectionKey))
            {
                if (!root.at(collectionKey).is_array())
                {
                    std::cout << contentType << " JSON file '" << filePath.string()
                        << "' field '" << collectionKey << "' must be an array.\n";
                    return false;
                }

                for (const json& entry : root.at(collectionKey))
                {
                    if (!entry.is_object())
                    {
                        std::cout << contentType << " JSON file '" << filePath.string()
                            << "' has a non-object entry in array field '"
                            << collectionKey << "'.\n";
                        return false;
                    }

                    outEntries.push_back(&entry);
                }
            }
            else
            {
                outEntries.push_back(&root);
            }
        }
        else
        {
            std::cout << contentType << " JSON file '" << filePath.string()
                << "' must contain an object, an array of objects, or an object with a '"
                << collectionKey << "' array.\n";
            return false;
        }

        if (outEntries.empty())
        {
            std::cout << contentType << " JSON file '" << filePath.string()
                << "' does not contain any entries.\n";
            return false;
        }

        return true;
    }

    bool parseEncounterObject(
        const json& encounterJson,
        const std::filesystem::path& filePath,
        EncounterData& outEncounter)
    {
        const json* mapData = nullptr;

        return requireString(encounterJson, "encounterId", filePath, outEncounter.encounterId) &&
            requireObject(encounterJson, "mapData", filePath, mapData) &&
            requireString(*mapData, "mapId", filePath, outEncounter.mapData.mapId) &&
            requireString(*mapData, "mapJsonPath", filePath, outEncounter.mapData.mapJsonPath) &&
            requireString(*mapData, "tilesetPath", filePath, outEncounter.mapData.tilesetPath) &&
            requireString(*mapData, "tilesetTexturePath", filePath, outEncounter.mapData.tilesetTexturePath) &&
            requireString(*mapData, "walkableLayerName", filePath, outEncounter.mapData.walkableLayerName) &&
            requireString(*mapData, "blockedLayerName", filePath, outEncounter.mapData.blockedLayerName) &&
            requireString(*mapData, "objectLayerName", filePath, outEncounter.mapData.objectLayerName);
    }

    bool parseEncounterFile(
        const std::filesystem::path& filePath,
        std::vector<EncounterData>& outEncounters)
    {
        json root;

        if (!readJsonFile(filePath, root))
        {
            return false;
        }

        std::vector<const json*> entries;

        if (!collectObjectEntries(root, "encounters", "Encounter", filePath, entries))
        {
            return false;
        }

        outEncounters.clear();

        for (const json* entry : entries)
        {
            EncounterData encounter;

            if (!parseEncounterObject(*entry, filePath, encounter))
            {
                return false;
            }

            outEncounters.push_back(encounter);
        }

        return true;
    }

    bool parseMissionObject(
        const json& missionJson,
        const std::filesystem::path& filePath,
        const std::unordered_map<std::string, EncounterData>& encountersById,
        MissionData& outMission)
    {
        std::vector<std::string> encounterIds;

        if (!requireString(missionJson, "missionId", filePath, outMission.missionId) ||
            !requireString(missionJson, "missionName", filePath, outMission.missionName) ||
            !requireString(missionJson, "missionDescription", filePath, outMission.missionDescription) ||
            !requireStringArray(missionJson, "encounterIds", filePath, encounterIds))
        {
            return false;
        }

        outMission.encounters.clear();

        for (const std::string& encounterId : encounterIds)
        {
            const auto encounterSearch = encountersById.find(encounterId);

            if (encounterSearch == encountersById.end())
            {
                std::cout << "Mission JSON file '" << filePath.string()
                    << "' references unknown encounterId '" << encounterId << "'.\n";
                return false;
            }

            outMission.encounters.push_back(encounterSearch->second);
        }

        return true;
    }

    bool parseMissionFile(
        const std::filesystem::path& filePath,
        const std::unordered_map<std::string, EncounterData>& encountersById,
        std::vector<MissionData>& outMissions)
    {
        json root;

        if (!readJsonFile(filePath, root))
        {
            return false;
        }

        std::vector<const json*> entries;

        if (!collectObjectEntries(root, "missions", "Mission", filePath, entries))
        {
            return false;
        }

        outMissions.clear();

        for (const json* entry : entries)
        {
            MissionData mission;

            if (!parseMissionObject(*entry, filePath, encountersById, mission))
            {
                return false;
            }

            outMissions.push_back(mission);
        }

        return true;
    }

    bool directoryExists(const std::filesystem::path& directory, const char* label)
    {
        if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory))
        {
            std::cout << label << " directory does not exist: "
                << directory.string() << "\n";
            return false;
        }

        return true;
    }
}

bool MissionDatabase::loadFromDirectories(
    const std::filesystem::path& missionsDirectory,
    const std::filesystem::path& encountersDirectory)
{
    if (!directoryExists(encountersDirectory, "Encounters") ||
        !directoryExists(missionsDirectory, "Missions"))
    {
        return false;
    }

    std::unordered_map<std::string, EncounterData> loadedEncounters;
    std::vector<MissionData> loadedMissions;
    std::set<std::string> loadedMissionIds;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(encountersDirectory))
    {
        if (!entry.is_regular_file() || !hasJsonExtension(entry.path()))
        {
            continue;
        }

        std::vector<EncounterData> encounters;

        if (!parseEncounterFile(entry.path(), encounters))
        {
            return false;
        }

        for (const EncounterData& encounter : encounters)
        {
            if (loadedEncounters.contains(encounter.encounterId))
            {
                std::cout << "Duplicate encounterId '" << encounter.encounterId
                    << "' found in file: " << entry.path().string() << "\n";
                return false;
            }

            loadedEncounters.emplace(encounter.encounterId, encounter);
        }
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(missionsDirectory))
    {
        if (!entry.is_regular_file() || !hasJsonExtension(entry.path()))
        {
            continue;
        }

        std::vector<MissionData> fileMissions;

        if (!parseMissionFile(entry.path(), loadedEncounters, fileMissions))
        {
            return false;
        }

        for (const MissionData& mission : fileMissions)
        {
            if (loadedMissionIds.contains(mission.missionId))
            {
                std::cout << "Duplicate missionId '" << mission.missionId
                    << "' found in file: " << entry.path().string() << "\n";
                return false;
            }

            loadedMissionIds.insert(mission.missionId);
            loadedMissions.push_back(mission);
        }
    }

    if (loadedEncounters.empty())
    {
        std::cout << "No encounter JSON files were loaded from: "
            << encountersDirectory.string() << "\n";
        return false;
    }

    if (loadedMissions.empty())
    {
        std::cout << "No mission JSON files were loaded from: "
            << missionsDirectory.string() << "\n";
        return false;
    }

    encountersById = std::move(loadedEncounters);
    missions = std::move(loadedMissions);

    std::cout << "Loaded " << encountersById.size() << " encounters and "
        << missions.size() << " missions.\n";

    return true;
}

const MissionData* MissionDatabase::findMission(const std::string& missionId) const
{
    for (const MissionData& mission : missions)
    {
        if (mission.missionId == missionId)
        {
            return &mission;
        }
    }

    return nullptr;
}

const EncounterData* MissionDatabase::findEncounter(const std::string& encounterId) const
{
    const auto encounterSearch = encountersById.find(encounterId);

    if (encounterSearch == encountersById.end())
    {
        return nullptr;
    }

    return &encounterSearch->second;
}

const std::vector<MissionData>& MissionDatabase::getMissions() const
{
    return missions;
}

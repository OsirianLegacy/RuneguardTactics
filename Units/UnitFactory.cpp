#include "UnitFactory.h"

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace
{
    std::string ReadTextFile(const std::filesystem::path& filePath)
    {
        std::ifstream file(filePath);
        if (!file)
        {
            throw std::runtime_error("Failed to open unit definition file: " + filePath.string());
        }

        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }

    std::size_t FindValueStart(const std::string& text, const std::string& key)
    {
        const std::string needle = "\"" + key + "\"";
        const std::size_t keyPos = text.find(needle);
        if (keyPos == std::string::npos)
        {
            throw std::runtime_error("Missing JSON key: " + key);
        }

        const std::size_t colonPos = text.find(':', keyPos + needle.size());
        if (colonPos == std::string::npos)
        {
            throw std::runtime_error("Missing ':' after JSON key: " + key);
        }

        const std::size_t valuePos = text.find_first_not_of(" \t\r\n", colonPos + 1);
        if (valuePos == std::string::npos)
        {
            throw std::runtime_error("Missing JSON value for key: " + key);
        }

        return valuePos;
    }

    std::string ExtractString(const std::string& text, const std::string& key)
    {
        const std::size_t valuePos = FindValueStart(text, key);
        if (text[valuePos] != '"')
        {
            throw std::runtime_error("Expected string value for key: " + key);
        }

        const std::size_t endQuote = text.find('"', valuePos + 1);
        if (endQuote == std::string::npos)
        {
            throw std::runtime_error("Unterminated string value for key: " + key);
        }

        return text.substr(valuePos + 1, endQuote - valuePos - 1);
    }

    int ExtractInt(const std::string& text, const std::string& key)
    {
        const std::size_t valuePos = FindValueStart(text, key);
        std::size_t endPos = valuePos;

        while (endPos < text.size())
        {
            const char c = text[endPos];
            if ((c >= '0' && c <= '9') || c == '-' || c == '+')
            {
                ++endPos;
                continue;
            }
            break;
        }

        if (endPos == valuePos)
        {
            throw std::runtime_error("Expected integer value for key: " + key);
        }

        return std::stoi(text.substr(valuePos, endPos - valuePos));
    }

    bool ExtractBool(const std::string& text, const std::string& key)
    {
        const std::size_t valuePos = FindValueStart(text, key);
        if (text.compare(valuePos, 4, "true") == 0)
        {
            return true;
        }

        if (text.compare(valuePos, 5, "false") == 0)
        {
            return false;
        }

        throw std::runtime_error("Expected boolean value for key: " + key);
    }

    TEAM ParseTeam(const std::string& value)
    {
        if (value == "PLAYER")
        {
            return PLAYER;
        }
        if (value == "ENEMY")
        {
            return ENEMY;
        }
        if (value == "CIVILIAN")
        {
            return CIVILIAN;
        }
        if (value == "NEUTRAL")
        {
            return NEUTRAL;
        }

        throw std::runtime_error("Unknown team value: " + value);
    }

    MOVETYPE ParseMoveType(const std::string& value)
    {
        if (value == "CARDINAL")
        {
            return CARDINAL;
        }
        if (value == "DIAGONAL")
        {
            return DIAGONAL;
        }
        if (value == "TELEPORT")
        {
            return TELEPORT;
        }

        throw std::runtime_error("Unknown movetype value: " + value);
    }
}

UnitFactory::UnitFactory(std::filesystem::path databaseDirectory)
    : databaseDirectory(std::move(databaseDirectory))
{
    LoadDefinitions();
}

void UnitFactory::LoadDefinitions()
{
    defs.clear();

    if (!std::filesystem::exists(databaseDirectory))
    {
        throw std::runtime_error("Unit database directory does not exist: " + databaseDirectory.string());
    }

    for (const auto& entry : std::filesystem::directory_iterator(databaseDirectory))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }

        if (entry.path().extension() != ".json")
        {
            continue;
        }

        LoadDefinitionFile(entry.path());
    }
}

void UnitFactory::LoadDefinitionFile(const std::filesystem::path& filePath)
{
    const std::string json = ReadTextFile(filePath);

    const std::string unitID = ExtractString(json, "UnitID");
    const std::string unitName = ExtractString(json, "UnitName");
    const TEAM team = ParseTeam(ExtractString(json, "team"));
    const MOVETYPE moveType = ParseMoveType(ExtractString(json, "movetype"));
    const int health = ExtractInt(json, "health");
    const int defense = ExtractInt(json, "defense");
    const int damage = ExtractInt(json, "damage");
    const int healing = ExtractInt(json, "healing");
    const int movement = ExtractInt(json, "movement");
    const int range = ExtractInt(json, "range");
    const int speed = ExtractInt(json, "speed");
    const bool isAI = ExtractBool(json, "isAI");

    defs.insert_or_assign(
        unitID,
        UnitDefinition(unitID, unitName, team, moveType, health, defense, damage, healing, movement, range, speed, isAI));
}

UnitBase UnitFactory::BuildUnit(const std::string& id) const
{
    const auto it = defs.find(id);
    if (it == defs.end())
    {
        throw std::out_of_range("Unknown unit id: " + id);
    }

    return UnitBase(it->second);
}

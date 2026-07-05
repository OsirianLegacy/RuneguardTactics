#include "UnitFactory.h"

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include <raylib.h>

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

    bool HasJsonKey(const std::string& text, const std::string& key)
    {
        const std::string needle = "\"" + key + "\"";
        return text.find(needle) != std::string::npos;
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

    std::string ExtractOptionalString(const std::string& text, const std::string& key)
    {
        if (!HasJsonKey(text, key))
        {
            return {};
        }

        return ExtractString(text, key);
    }

    std::filesystem::path ResolveTexturePath(
        const std::filesystem::path& definitionFilePath,
        const std::string& texturePath)
    {
        std::filesystem::path resolvedPath(texturePath);

        if (resolvedPath.is_absolute() || std::filesystem::exists(resolvedPath))
        {
            return resolvedPath;
        }

        const std::filesystem::path relativeToDefinition = definitionFilePath.parent_path() / resolvedPath;

        if (std::filesystem::exists(relativeToDefinition))
        {
            return relativeToDefinition;
        }

        return resolvedPath;
    }

    Texture2D LoadOptionalTexture(
        const std::filesystem::path& definitionFilePath,
        const std::string& texturePath)
    {
        if (texturePath.empty())
        {
            return Texture2D{};
        }

        const std::filesystem::path resolvedPath = ResolveTexturePath(definitionFilePath, texturePath);
        return LoadTexture(resolvedPath.string().c_str());
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

    int ExtractOptionalInt(const std::string& text, const std::string& key, const int fallback)
    {
        if (!HasJsonKey(text, key))
        {
            return fallback;
        }

        return ExtractInt(text, key);
    }

    std::vector<int> ExtractOptionalIntArray(const std::string& text, const std::string& key)
    {
        std::vector<int> values;

        if (!HasJsonKey(text, key))
        {
            return values;
        }

        const std::size_t valuePos = FindValueStart(text, key);

        if (text[valuePos] != '[')
        {
            throw std::runtime_error("Expected array value for key: " + key);
        }

        const std::size_t endBracket = text.find(']', valuePos + 1);

        if (endBracket == std::string::npos)
        {
            throw std::runtime_error("Unterminated array value for key: " + key);
        }

        std::string arrayText = text.substr(valuePos + 1, endBracket - valuePos - 1);
        std::stringstream stream(arrayText);
        std::string token;

        while (std::getline(stream, token, ','))
        {
            const std::size_t tokenStart = token.find_first_not_of(" \t\r\n");

            if (tokenStart == std::string::npos)
            {
                continue;
            }

            values.push_back(std::stoi(token.substr(tokenStart)));
        }

        return values;
    }

    Rectangle MakeFrameRectangle(
        const Texture2D& texture,
        const int frameWidth,
        const int frameHeight,
        const int frameIndex)
    {
        if (texture.id == 0 || frameWidth <= 0 || frameHeight <= 0)
        {
            return Rectangle{};
        }

        const int columns = std::max(1, texture.width / frameWidth);
        const int sourceX = (frameIndex % columns) * frameWidth;
        const int sourceY = (frameIndex / columns) * frameHeight;

        return Rectangle{
            static_cast<float>(sourceX),
            static_cast<float>(sourceY),
            static_cast<float>(frameWidth),
            static_cast<float>(frameHeight)
        };
    }

    std::array<Rectangle, 4> BuildFrameRectangles(
        const Texture2D& texture,
        const int frameWidth,
        const int frameHeight,
        const std::vector<int>& frameIndices)
    {
        std::array<Rectangle, 4> frames{};

        for (std::size_t index = 0; index < frames.size(); ++index)
        {
            const int frameIndex = index < frameIndices.size() ? frameIndices[index] : 0;
            frames[index] = MakeFrameRectangle(texture, frameWidth, frameHeight, frameIndex);
        }

        return frames;
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
    UnitSpriteSheet spriteSheet;
    spriteSheet.texture = LoadOptionalTexture(filePath, ExtractOptionalString(json, "unitTexture"));
    spriteSheet.frameWidth = ExtractOptionalInt(json, "frameWidth", 0);
    spriteSheet.frameHeight = ExtractOptionalInt(json, "frameHeight", 0);
    spriteSheet.idleFrames = BuildFrameRectangles(
        spriteSheet.texture,
        spriteSheet.frameWidth,
        spriteSheet.frameHeight,
        ExtractOptionalIntArray(json, "idleFrames"));
    spriteSheet.damagedFrames = BuildFrameRectangles(
        spriteSheet.texture,
        spriteSheet.frameWidth,
        spriteSheet.frameHeight,
        ExtractOptionalIntArray(json, "damagedFrames"));
    spriteSheet.healedFrames = BuildFrameRectangles(
        spriteSheet.texture,
        spriteSheet.frameWidth,
        spriteSheet.frameHeight,
        ExtractOptionalIntArray(json, "healedFrames"));
    spriteSheet.highlightedFrames = BuildFrameRectangles(
        spriteSheet.texture,
        spriteSheet.frameWidth,
        spriteSheet.frameHeight,
        ExtractOptionalIntArray(json, "highlightedFrames"));
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
        UnitDefinition(
            unitID,
            unitName,
            team,
            moveType,
            spriteSheet,
            health,
            defense,
            damage,
            healing,
            movement,
            range,
            speed,
            isAI));
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

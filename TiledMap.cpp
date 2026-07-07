#include "TiledMap.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace
{
    constexpr unsigned int FlippedHorizontallyFlag = 0x80000000;
    constexpr unsigned int FlippedVerticallyFlag = 0x40000000;
    constexpr unsigned int FlippedDiagonallyFlag = 0x20000000;
    constexpr unsigned int TiledFlipFlags =
        FlippedHorizontallyFlag | FlippedVerticallyFlag | FlippedDiagonallyFlag;

    std::string readTextFile(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            return {};
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    size_t findMatchingBrace(const std::string& text, size_t openBrace)
    {
        int depth = 0;

        for (size_t i = openBrace; i < text.size(); i++)
        {
            if (text[i] == '{')
            {
                depth++;
            }
            else if (text[i] == '}')
            {
                depth--;

                if (depth == 0)
                {
                    return i;
                }
            }
        }

        return std::string::npos;
    }
    // finds the matching ] for a specific [ already found, not necessarily the last ]. This is used to find the start and end of each individual layer.
    size_t findMatchingBracket(const std::string& text, size_t openBracket)
    {
        int depth = 0;

        for (size_t i = openBracket; i < text.size(); i++)
        {
            if (text[i] == '[')
            {
                depth++;
            }
            else if (text[i] == ']')
            {
                depth--;

                if (depth == 0)
                {
                    return i;
                }
            }
        }

        return std::string::npos;
    }
    // this function converts the grid itself into valid logic->gridmap coords and determines the following: cells map width, cells map height, cells tile size
    // Calculation for Tileds flat-grid (1D Array) is tileIndex = y * layer.width + x; tileId = layer.data[tileIndex];
    // When Read
    int readIntProperty(const std::string& text, const std::string& key, size_t start = 0)
    {
        const std::string quotedKey = "\"" + key + "\"";
        size_t keyPosition = text.find(quotedKey, start);

        if (keyPosition == std::string::npos)
        {
            return 0;
        }

        size_t colonPosition = text.find(':', keyPosition);
        size_t valuePosition = colonPosition + 1;

        while (valuePosition < text.size() && std::isspace(static_cast<unsigned char>(text[valuePosition])))
        {
            valuePosition++;
        }

        return std::stoi(text.substr(valuePosition));
    }

    bool readBoolProperty(const std::string& text, const std::string& key, bool fallback = false)
    {
        const std::string quotedKey = "\"" + key + "\"";
        size_t keyPosition = text.find(quotedKey);

        if (keyPosition == std::string::npos)
        {
            return fallback;
        }

        size_t colonPosition = text.find(':', keyPosition);
        size_t valuePosition = colonPosition + 1;

        while (valuePosition < text.size() && std::isspace(static_cast<unsigned char>(text[valuePosition])))
        {
            valuePosition++;
        }

        return text.compare(valuePosition, 4, "true") == 0;
    }

    std::string readStringProperty(const std::string& text, const std::string& key)
    {
        const std::string quotedKey = "\"" + key + "\"";
        size_t keyPosition = text.find(quotedKey);

        if (keyPosition == std::string::npos)
        {
            return {};
        }

        size_t firstQuote = text.find('"', text.find(':', keyPosition));
        size_t secondQuote = text.find('"', firstQuote + 1);

        if (firstQuote == std::string::npos || secondQuote == std::string::npos)
        {
            return {};
        }

        return text.substr(firstQuote + 1, secondQuote - firstQuote - 1);
    }

    size_t findTopLevelJsonKey(const std::string& text, const std::string& key)
    {
        const std::string quotedKey = "\"" + key + "\"";
        int depth = 0;
        bool inString = false;
        bool escaped = false;

        for (size_t i = 0; i < text.size(); i++)
        {
            const char current = text[i];

            if (inString)
            {
                if (escaped)
                {
                    escaped = false;
                }
                else if (current == '\\')
                {
                    escaped = true;
                }
                else if (current == '"')
                {
                    inString = false;
                }

                continue;
            }

            if (current == '"')
            {
                if (depth == 1 && text.compare(i, quotedKey.size(), quotedKey) == 0)
                {
                    return i;
                }

                inString = true;
            }
            else if (current == '{' || current == '[')
            {
                depth++;
            }
            else if (current == '}' || current == ']')
            {
                depth--;
            }
        }

        return std::string::npos;
    }

    size_t findJsonValueStart(const std::string& text, const std::string& key)
    {
        const size_t keyPosition = findTopLevelJsonKey(text, key);

        if (keyPosition == std::string::npos)
        {
            return std::string::npos;
        }

        const size_t colonPosition = text.find(':', keyPosition);

        if (colonPosition == std::string::npos)
        {
            return std::string::npos;
        }

        size_t valuePosition = colonPosition + 1;

        while (valuePosition < text.size() && std::isspace(static_cast<unsigned char>(text[valuePosition])))
        {
            valuePosition++;
        }

        return valuePosition;
    }

    std::string readTopLevelStringProperty(const std::string& text, const std::string& key)
    {
        const size_t valuePosition = findJsonValueStart(text, key);

        if (valuePosition == std::string::npos || valuePosition >= text.size() || text[valuePosition] != '"')
        {
            return {};
        }

        const size_t valueEnd = text.find('"', valuePosition + 1);

        if (valueEnd == std::string::npos)
        {
            return {};
        }

        return text.substr(valuePosition + 1, valueEnd - valuePosition - 1);
    }

    std::string readTopLevelValueAsString(const std::string& text, const std::string& key)
    {
        const size_t valuePosition = findJsonValueStart(text, key);

        if (valuePosition == std::string::npos || valuePosition >= text.size())
        {
            return {};
        }

        if (text[valuePosition] == '"')
        {
            const size_t valueEnd = text.find('"', valuePosition + 1);

            if (valueEnd == std::string::npos)
            {
                return {};
            }

            return text.substr(valuePosition + 1, valueEnd - valuePosition - 1);
        }

        size_t valueEnd = valuePosition;

        while (valueEnd < text.size() && text[valueEnd] != ',' && text[valueEnd] != '}')
        {
            valueEnd++;
        }

        std::string value = text.substr(valuePosition, valueEnd - valuePosition);
        while (!value.empty() && std::isspace(static_cast<unsigned char>(value.back())))
        {
            value.pop_back();
        }

        return value;
    }

    int readTopLevelIntProperty(const std::string& text, const std::string& key, int fallback = 0)
    {
        const size_t valuePosition = findJsonValueStart(text, key);

        if (valuePosition == std::string::npos)
        {
            return fallback;
        }

        return std::stoi(text.substr(valuePosition));
    }

    float readTopLevelFloatProperty(const std::string& text, const std::string& key, float fallback = 0.0f)
    {
        const size_t valuePosition = findJsonValueStart(text, key);

        if (valuePosition == std::string::npos)
        {
            return fallback;
        }

        return std::stof(text.substr(valuePosition));
    }

    bool readTopLevelBoolProperty(const std::string& text, const std::string& key, bool fallback = false)
    {
        const size_t valuePosition = findJsonValueStart(text, key);

        if (valuePosition == std::string::npos)
        {
            return fallback;
        }

        return text.compare(valuePosition, 4, "true") == 0;
    }

    std::string readXmlAttribute(const std::string& text, const std::string& key)
    {
        const std::string attributeKey = key + "=\"";
        const size_t keyPosition = text.find(attributeKey);

        if (keyPosition == std::string::npos)
        {
            return {};
        }

        const size_t valueStart = keyPosition + attributeKey.size();
        const size_t valueEnd = text.find('"', valueStart);

        if (valueEnd == std::string::npos)
        {
            return {};
        }

        return text.substr(valueStart, valueEnd - valueStart);
    }

    std::vector<int> readIntArrayProperty(const std::string& text, const std::string& key)
    {
        std::vector<int> values;
        const std::string quotedKey = "\"" + key + "\"";
        size_t keyPosition = text.find(quotedKey);

        if (keyPosition == std::string::npos)
        {
            return values;
        }

        size_t openBracket = text.find('[', keyPosition);
        size_t closeBracket = findMatchingBracket(text, openBracket);

        if (openBracket == std::string::npos || closeBracket == std::string::npos)
        {
            return values;
        }

        std::string arrayText = text.substr(openBracket + 1, closeBracket - openBracket - 1);
        std::stringstream stream(arrayText);
        std::string token;

        while (std::getline(stream, token, ','))
        {
            values.push_back(std::stoi(token));
        }

        return values;
    }

    std::vector<std::string> readTopLevelObjectArray(const std::string& text, const std::string& key)
    {
        std::vector<std::string> objects;
        const size_t valuePosition = findJsonValueStart(text, key);

        if (valuePosition == std::string::npos || valuePosition >= text.size() || text[valuePosition] != '[')
        {
            return objects;
        }

        const size_t closeBracket = findMatchingBracket(text, valuePosition);

        if (closeBracket == std::string::npos)
        {
            return objects;
        }

        size_t searchPosition = valuePosition + 1;

        while (searchPosition < closeBracket)
        {
            const size_t objectOpenBrace = text.find('{', searchPosition);

            if (objectOpenBrace == std::string::npos || objectOpenBrace > closeBracket)
            {
                break;
            }

            const size_t objectCloseBrace = findMatchingBrace(text, objectOpenBrace);

            if (objectCloseBrace == std::string::npos)
            {
                break;
            }

            objects.push_back(text.substr(objectOpenBrace, objectCloseBrace - objectOpenBrace + 1));
            searchPosition = objectCloseBrace + 1;
        }

        return objects;
    }

    int clearTiledFlipFlags(int tileId)
    {
        return static_cast<int>(static_cast<unsigned int>(tileId) & ~TiledFlipFlags);
    }

    celltype cellTypeFromString(const std::string& value)
    {
        if (value == "ground" || value == "Ground")
        {
            return celltype::ground;
        }

        if (value == "wall" || value == "Wall")
        {
            return celltype::wall;
        }

        if (value == "water" || value == "Water")
        {
            return celltype::water;
        }

        return celltype::empty;
    }

    TiledTileProperties readTileProperties(const std::string& tileText)
    {
        TiledTileProperties properties;
        const std::string tileType = readStringProperty(tileText, "type");
        const std::string tileClass = readStringProperty(tileText, "class");
        properties.isObject = tileType == "Object" || tileClass == "Object";
        size_t searchPosition = 0;

        while (true)
        {
            const size_t propertyOpenBrace = tileText.find('{', searchPosition);

            if (propertyOpenBrace == std::string::npos)
            {
                break;
            }

            const size_t propertyCloseBrace = findMatchingBrace(tileText, propertyOpenBrace);

            if (propertyCloseBrace == std::string::npos)
            {
                break;
            }

            const std::string propertyText =
                tileText.substr(propertyOpenBrace, propertyCloseBrace - propertyOpenBrace + 1);
            const std::string propertyName = readStringProperty(propertyText, "name");

            if (propertyName == "walkable")
            {
                properties.hasWalkable = true;
                properties.walkable = readBoolProperty(propertyText, "value", false);
            }
            else if (propertyName == "cost")
            {
                properties.hasCost = true;
                properties.cost = readIntProperty(propertyText, "value");
            }
            else if (propertyName == "celltype" || propertyName == "type")
            {
                properties.hasCellType = true;
                properties.type = cellTypeFromString(readStringProperty(propertyText, "value"));
            }

            searchPosition = propertyCloseBrace + 1;
        }

        if (properties.isObject && !properties.hasWalkable)
        {
            properties.hasWalkable = true;
            properties.walkable = false;
        }

        return properties;
    }

    TiledTileProperties readTsxTileProperties(const std::string& tileText)
    {
        TiledTileProperties properties;
        const size_t tileOpenEnd = tileText.find('>');

        if (tileOpenEnd != std::string::npos)
        {
            const std::string tileTag = tileText.substr(0, tileOpenEnd + 1);
            const std::string tileType = readXmlAttribute(tileTag, "type");
            const std::string tileClass = readXmlAttribute(tileTag, "class");
            properties.isObject = tileType == "Object" || tileClass == "Object";
        }

        size_t searchPosition = 0;

        while (true)
        {
            const size_t propertyStart = tileText.find("<property", searchPosition);

            if (propertyStart == std::string::npos)
            {
                break;
            }

            const size_t propertyEnd = tileText.find("/>", propertyStart);

            if (propertyEnd == std::string::npos)
            {
                break;
            }

            const std::string propertyText =
                tileText.substr(propertyStart, propertyEnd - propertyStart + 2);
            const std::string propertyName = readXmlAttribute(propertyText, "name");
            const std::string propertyValue = readXmlAttribute(propertyText, "value");

            if (propertyName == "walkable")
            {
                properties.hasWalkable = true;
                properties.walkable = propertyValue == "true";
            }
            else if (propertyName == "cost")
            {
                properties.hasCost = true;
                properties.cost = std::stoi(propertyValue);
            }
            else if (propertyName == "celltype" || propertyName == "type")
            {
                properties.hasCellType = true;
                properties.type = cellTypeFromString(propertyValue);
            }

            searchPosition = propertyEnd + 2;
        }

        if (properties.isObject && !properties.hasWalkable)
        {
            properties.hasWalkable = true;
            properties.walkable = false;
        }

        return properties;
    }

    TiledObjectProperty readTiledObjectProperty(const std::string& propertyText)
    {
        TiledObjectProperty property;
        property.name = readTopLevelStringProperty(propertyText, "name");
        property.type = readTopLevelStringProperty(propertyText, "type");
        property.propertyType = readTopLevelStringProperty(propertyText, "propertytype");
        property.value = readTopLevelValueAsString(propertyText, "value");
        return property;
    }

    TiledObject readTiledObject(const std::string& objectText)
    {
        TiledObject object;
        object.id = readTopLevelIntProperty(objectText, "id");
        object.name = readTopLevelStringProperty(objectText, "name");
        object.type = readTopLevelStringProperty(objectText, "type");
        object.className = readTopLevelStringProperty(objectText, "class");
        object.x = readTopLevelFloatProperty(objectText, "x");
        object.y = readTopLevelFloatProperty(objectText, "y");
        object.width = readTopLevelFloatProperty(objectText, "width");
        object.height = readTopLevelFloatProperty(objectText, "height");
        object.visible = readTopLevelBoolProperty(objectText, "visible", true);

        for (const std::string& propertyText : readTopLevelObjectArray(objectText, "properties"))
        {
            object.properties.push_back(readTiledObjectProperty(propertyText));
        }

        return object;
    }

    TiledObjectLayer readTiledObjectLayer(const std::string& layerText)
    {
        TiledObjectLayer layer;
        layer.name = readTopLevelStringProperty(layerText, "name");
        layer.type = readTopLevelStringProperty(layerText, "type");
        layer.className = readTopLevelStringProperty(layerText, "class");
        layer.visible = readTopLevelBoolProperty(layerText, "visible", true);

        for (const std::string& objectText : readTopLevelObjectArray(layerText, "objects"))
        {
            layer.objects.push_back(readTiledObject(objectText));
        }

        return layer;
    }

    std::string getObjectPropertyValue(const TiledObject& object, const std::string& propertyName)
    {
        for (const TiledObjectProperty& property : object.properties)
        {
            if (property.name == propertyName)
            {
                return property.value;
            }
        }

        return {};
    }

    coord getObjectGridCoordinate(const TiledObject& object, const int tileWidth, const int tileHeight)
    {
        return coord{
            static_cast<int>((object.x + static_cast<float>(tileWidth) / 2.0f) / static_cast<float>(tileWidth)),
            static_cast<int>((object.y + static_cast<float>(tileHeight) / 2.0f) / static_cast<float>(tileHeight))
        };
    }

    std::optional<TEAM> teamFromString(const std::string& value)
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

        return std::nullopt;
    }

    void logInvalidSpawnMarker(
        const std::string& layerName,
        const TiledObject& object,
        const std::string& reason)
    {
        std::cout << "Skipping invalid spawn marker on layer '" << layerName
            << "' object id " << object.id << ": " << reason << "\n";
    }

    bool hasAnyProperty(const TiledTileProperties& properties)
    {
        return properties.isObject || properties.hasWalkable || properties.hasCost || properties.hasCellType;
    }

    void applyTileProperties(cell& targetCell, const TiledTileProperties& properties)
    {
        if (properties.hasWalkable)
        {
            targetCell.walkable = properties.walkable;
        }

        if (properties.hasCost)
        {
            targetCell.cost = properties.cost;
        }

        if (properties.hasCellType)
        {
            targetCell.type = properties.type;

            if (!properties.hasWalkable && properties.type == celltype::wall)
            {
                targetCell.walkable = false;
            }
        }
    }

    void applyLayerProperties(
        const TiledLayer& layer,
        const std::map<int, TiledTileProperties>& tileProperties,
        GridLogic& gridlogic)
    {
        for (int y = 0; y < layer.height; y++)
        {
            for (int x = 0; x < layer.width; x++)
            {
                const int tileIndex = y * layer.width + x;

                if (tileIndex < 0 || tileIndex >= static_cast<int>(layer.data.size()))
                {
                    continue;
                }

                const int tileId = clearTiledFlipFlags(layer.data[tileIndex]);

                if (tileId == 0)
                {
                    continue;
                }

                const auto propertySearch = tileProperties.find(tileId);

                if (propertySearch == tileProperties.end())
                {
                    continue;
                }

                coord coordinate{x, y};

                if (gridlogic.gridmap.contains(coordinate))
                {
                    applyTileProperties(gridlogic.gridmap.at(coordinate), propertySearch->second);
                }
            }
        }
    }
}
// Combat Manager calls this function when loading an encounter's data to fetch the map data from Tiled.json file.
bool TiledMap::loadFromJson(const std::string& mapPath)
{
    const std::string mapText = readTextFile(mapPath);

    if (mapText.empty())
    {
        std::cout << "Failed to load Tiled map: " << mapPath << "\n";
        return false;
    }

    height = readIntProperty(mapText, "height");
    tileWidth = readIntProperty(mapText, "tilewidth");
    tileHeight = readIntProperty(mapText, "tileheight");
    width = readIntProperty(mapText, "width", mapText.rfind("\"version\""));

    layers.clear();
    objectLayers.clear();
    tileProperties.clear();

    const size_t layersKey = mapText.find("\"layers\"");
    const size_t layersOpenBracket = mapText.find('[', layersKey);
    const size_t layersCloseBracket = findMatchingBracket(mapText, layersOpenBracket);

    if (layersKey == std::string::npos ||
        layersOpenBracket == std::string::npos ||
        layersCloseBracket == std::string::npos)
    {
        std::cout << "Tiled map has no readable layers: " << mapPath << "\n";
        return false;
    }

    size_t searchPosition = layersOpenBracket;

    while (searchPosition < layersCloseBracket)
    {
        size_t layerOpenBrace = mapText.find('{', searchPosition);

        if (layerOpenBrace == std::string::npos || layerOpenBrace > layersCloseBracket)
        {
            break;
        }

        size_t layerCloseBrace = findMatchingBrace(mapText, layerOpenBrace);

        if (layerCloseBrace == std::string::npos)
        {
            break;
        }

        const std::string layerText =
            mapText.substr(layerOpenBrace, layerCloseBrace - layerOpenBrace + 1);

        const std::string layerType = readTopLevelStringProperty(layerText, "type");

        if (layerType == "tilelayer")
        {
            TiledLayer layer;
            layer.name = readTopLevelStringProperty(layerText, "name");
            layer.width = readTopLevelIntProperty(layerText, "width");
            layer.height = readTopLevelIntProperty(layerText, "height");
            layer.visible = readTopLevelBoolProperty(layerText, "visible", true);
            layer.data = readIntArrayProperty(layerText, "data");
            layers.push_back(layer);
        }
        else if (layerType == "objectgroup")
        {
            objectLayers.push_back(readTiledObjectLayer(layerText));
        }

        searchPosition = layerCloseBrace + 1;
    }

    const size_t tilesetsKey = mapText.find("\"tilesets\"");
    const size_t tilesetOpenBrace = mapText.find('{', tilesetsKey);

    if (tilesetsKey != std::string::npos && tilesetOpenBrace != std::string::npos)
    {
        const size_t tilesetCloseBrace = findMatchingBrace(mapText, tilesetOpenBrace);
        const std::string tilesetText =
            mapText.substr(tilesetOpenBrace, tilesetCloseBrace - tilesetOpenBrace + 1);
        tileset.firstGid = readIntProperty(tilesetText, "firstgid");

        const size_t tilesKey = tilesetText.find("\"tiles\"");
        const size_t tilesOpenBracket = tilesetText.find('[', tilesKey);
        const size_t tilesCloseBracket = findMatchingBracket(tilesetText, tilesOpenBracket);

        if (tilesKey != std::string::npos &&
            tilesOpenBracket != std::string::npos &&
            tilesCloseBracket != std::string::npos)
        {
            size_t tileSearchPosition = tilesOpenBracket;

            while (tileSearchPosition < tilesCloseBracket)
            {
                const size_t tileOpenBrace = tilesetText.find('{', tileSearchPosition);

                if (tileOpenBrace == std::string::npos || tileOpenBrace > tilesCloseBracket)
                {
                    break;
                }

                const size_t tileCloseBrace = findMatchingBrace(tilesetText, tileOpenBrace);

                if (tileCloseBrace == std::string::npos)
                {
                    break;
                }

                const std::string tileText =
                    tilesetText.substr(tileOpenBrace, tileCloseBrace - tileOpenBrace + 1);
                const int localTileId = readIntProperty(tileText, "id");
                const TiledTileProperties properties = readTileProperties(tileText);

                if (hasAnyProperty(properties))
                {
                    tileProperties.emplace(tileset.firstGid + localTileId, properties);
                }

                tileSearchPosition = tileCloseBrace + 1;
            }
        }
    }

    tileset.tileWidth = tileWidth;
    tileset.tileHeight = tileHeight;
    tileset.sourceTileWidth = tileWidth / 2;
    tileset.sourceTileHeight = tileHeight / 2;

    return true;
}

bool TiledMap::loadTilesetFromTsx(const std::string& tilesetPath)
{
    const std::string tilesetText = readTextFile(tilesetPath);

    if (tilesetText.empty())
    {
        std::cout << "Failed to load Tiled tileset: " << tilesetPath << "\n";
        return false;
    }

    const size_t tilesetStart = tilesetText.find("<tileset");
    const size_t tilesetEnd = tilesetText.find('>', tilesetStart);

    if (tilesetStart == std::string::npos || tilesetEnd == std::string::npos)
    {
        std::cout << "Tiled tileset has no readable tileset tag: " << tilesetPath << "\n";
        return false;
    }

    const std::string tilesetTag = tilesetText.substr(tilesetStart, tilesetEnd - tilesetStart + 1);
    const std::string sourceTileWidth = readXmlAttribute(tilesetTag, "tilewidth");
    const std::string sourceTileHeight = readXmlAttribute(tilesetTag, "tileheight");

    if (!sourceTileWidth.empty())
    {
        tileset.sourceTileWidth = std::stoi(sourceTileWidth);
    }

    if (!sourceTileHeight.empty())
    {
        tileset.sourceTileHeight = std::stoi(sourceTileHeight);
    }

    size_t searchPosition = 0;

    while (true)
    {
        const size_t tileStart = tilesetText.find("<tile", searchPosition);

        if (tileStart == std::string::npos)
        {
            break;
        }

        const size_t tileOpenEnd = tilesetText.find('>', tileStart);
        const size_t tileClose = tilesetText.find("</tile>", tileOpenEnd);

        if (tileOpenEnd == std::string::npos || tileClose == std::string::npos)
        {
            break;
        }

        const std::string tileText = tilesetText.substr(tileStart, tileClose - tileStart + 7);
        const std::string localTileIdText = readXmlAttribute(tileText, "id");

        if (!localTileIdText.empty())
        {
            const int localTileId = std::stoi(localTileIdText);
            const TiledTileProperties properties = readTsxTileProperties(tileText);

            if (hasAnyProperty(properties))
            {
                tileProperties[tileset.firstGid + localTileId] = properties;
            }
        }

        searchPosition = tileClose + 7;
    }

    return true;
}

void TiledMap::loadTilesetTexture(const std::string& texturePath)
{
    tileset.texture = LoadTexture(texturePath.c_str());
}

void TiledMap::unloadTextures() const
{
    UnloadTexture(tileset.texture);
}

const TiledLayer* TiledMap::getLayerByName(const std::string& layerName) const
{
    for (const TiledLayer& layer : layers)
    {
        if (layer.name == layerName)
        {
            return &layer;
        }
    }

    return nullptr;
}

const TiledObjectLayer* TiledMap::getObjectLayerByName(const std::string& layerName) const
{
    for (const TiledObjectLayer& layer : objectLayers)
    {
        if (layer.name == layerName)
        {
            return &layer;
        }
    }

    return nullptr;
}

std::vector<DeploymentSlot> TiledMap::getDeploymentSlots(const std::string& layerName) const
{
    std::vector<DeploymentSlot> deploymentSlots;
    const TiledObjectLayer* layer = getObjectLayerByName(layerName);

    if (layer == nullptr)
    {
        return deploymentSlots;
    }

    for (const TiledObject& object : layer->objects)
    {
        const std::string spawnType = getObjectPropertyValue(object, "spawnType");

        if (spawnType.empty() || spawnType != "PlayerDeploymentSlot")
        {
            continue;
        }

        const std::string spawnId = getObjectPropertyValue(object, "spawnId");

        if (spawnId.empty())
        {
            logInvalidSpawnMarker(layerName, object, "missing spawnId");
            continue;
        }

        deploymentSlots.push_back(DeploymentSlot{spawnId, getObjectGridCoordinate(object, tileWidth, tileHeight)});
    }

    return deploymentSlots;
}

std::vector<EncounterSpawn> TiledMap::getEncounterSpawns(const std::string& layerName) const
{
    std::vector<EncounterSpawn> encounterSpawns;
    const TiledObjectLayer* layer = getObjectLayerByName(layerName);

    if (layer == nullptr)
    {
        return encounterSpawns;
    }

    for (const TiledObject& object : layer->objects)
    {
        const std::string spawnType = getObjectPropertyValue(object, "spawnType");

        if (spawnType.empty() || spawnType != "EncounterSpawn")
        {
            continue;
        }

        const std::string spawnId = getObjectPropertyValue(object, "spawnId");
        const std::string unitId = getObjectPropertyValue(object, "unitId");
        const std::string teamValue = getObjectPropertyValue(object, "team");

        if (spawnId.empty())
        {
            logInvalidSpawnMarker(layerName, object, "missing spawnId");
            continue;
        }

        if (unitId.empty())
        {
            logInvalidSpawnMarker(layerName, object, "missing unitId");
            continue;
        }

        const std::optional<TEAM> team = teamFromString(teamValue);

        if (!team.has_value())
        {
            logInvalidSpawnMarker(layerName, object, "missing or unknown team '" + teamValue + "'");
            continue;
        }

        encounterSpawns.push_back(
            EncounterSpawn{spawnId, unitId, getObjectGridCoordinate(object, tileWidth, tileHeight), team.value()});
    }

    return encounterSpawns;
}

void TiledMap::draw(int startX, int startY) const
{
    draw(startX, startY, tileWidth);
}

void TiledMap::draw(int startX, int startY, int renderTileSize) const
{
    if (tileset.texture.id == 0)
    {
        return;
    }

    const int tilesPerRow = tileset.texture.width / tileset.sourceTileWidth;

    if (tilesPerRow <= 0)
    {
        return;
    }

    for (const TiledLayer& layer : layers)
    {
        if (!layer.visible)
        {
            continue;
        }

        for (int y = 0; y < layer.height; y++)
        {
            for (int x = 0; x < layer.width; x++)
            {
                const int tileIndex = y * layer.width + x;

                if (tileIndex < 0 || tileIndex >= static_cast<int>(layer.data.size()))
                {
                    continue;
                }

                const int tileId = clearTiledFlipFlags(layer.data[tileIndex]);

                if (tileId == 0)
                {
                    continue;
                }

                const int localId = tileId - tileset.firstGid;

                if (localId < 0)
                {
                    continue;
                }

                const int sourceX = (localId % tilesPerRow) * tileset.sourceTileWidth;
                const int sourceY = (localId / tilesPerRow) * tileset.sourceTileHeight;

                Rectangle source = {
                    static_cast<float>(sourceX),
                    static_cast<float>(sourceY),
                    static_cast<float>(tileset.sourceTileWidth),
                    static_cast<float>(tileset.sourceTileHeight)
                };

                Rectangle dest = {
                    static_cast<float>(startX + x * renderTileSize),
                    static_cast<float>(startY + y * renderTileSize),
                    static_cast<float>(renderTileSize),
                    static_cast<float>(renderTileSize)
                };

                DrawTexturePro(tileset.texture, source, dest, Vector2{0, 0}, 0.0f, WHITE);
            }
        }
    }
}

void TiledMap::initializeGrid(GridLogic& gridlogic, const std::string& blockedLayerName) const
{
    initializeGrid(gridlogic, "Ground", blockedLayerName);
}

void TiledMap::initializeGrid(
    GridLogic& gridlogic,
    const std::string& walkableLayerName,
    const std::string& blockedLayerName) const
{
    initializeGrid(gridlogic, walkableLayerName, blockedLayerName, "Objects");
}

void TiledMap::initializeGrid(
    GridLogic& gridlogic,
    const std::string& walkableLayerName,
    const std::string& blockedLayerName,
    const std::string& objectLayerName) const
{
    gridlogic.gridwidth = width;
    gridlogic.gridheight = height;
    gridlogic.gridmap.clear();

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            coord coordinate{x, y};
            cell newCell;
            newCell.coordinates = coordinate;
            newCell.walkable = false;
            newCell.cost = 0;
            newCell.type = celltype::empty;
            gridlogic.gridmap.emplace(coordinate, newCell);
        }
    }

    const TiledLayer* walkableLayer = getLayerByName(walkableLayerName);
    const TiledLayer* objectLayer = getLayerByName(objectLayerName);

    if (!tileProperties.empty())
    {
        for (const TiledLayer& layer : layers)
        {
            if (objectLayer != nullptr && &layer == objectLayer)
            {
                continue;
            }

            applyLayerProperties(layer, tileProperties, gridlogic);
        }

        if (objectLayer != nullptr)
        {
            applyLayerProperties(*objectLayer, tileProperties, gridlogic);
        }

        return;
    }

    if (walkableLayer != nullptr)
    {
        for (int y = 0; y < walkableLayer->height; y++)
        {
            for (int x = 0; x < walkableLayer->width; x++)
            {
                const int tileIndex = y * walkableLayer->width + x;

                if (tileIndex < 0 || tileIndex >= static_cast<int>(walkableLayer->data.size()))
                {
                    continue;
                }

                if (clearTiledFlipFlags(walkableLayer->data[tileIndex]) == 0)
                {
                    continue;
                }

                coord coordinate{x, y};

                if (gridlogic.gridmap.contains(coordinate))
                {
                    gridlogic.gridmap.at(coordinate).walkable = true;
                    gridlogic.gridmap.at(coordinate).cost = 1;
                    gridlogic.gridmap.at(coordinate).type = celltype::ground;
                }
            }
        }
    }

    const TiledLayer* blockedLayer = getLayerByName(blockedLayerName);

    if (blockedLayer == nullptr)
    {
        return;
    }

    for (int y = 0; y < blockedLayer->height; y++)
    {
        for (int x = 0; x < blockedLayer->width; x++)
        {
            const int tileIndex = y * blockedLayer->width + x;

            if (tileIndex < 0 || tileIndex >= static_cast<int>(blockedLayer->data.size()))
            {
                continue;
            }

            if (clearTiledFlipFlags(blockedLayer->data[tileIndex]) == 0)
            {
                continue;
            }

            coord coordinate{x, y};

            if (gridlogic.gridmap.contains(coordinate))
            {
                gridlogic.gridmap.at(coordinate).walkable = false;
                gridlogic.gridmap.at(coordinate).cost = 0;
                gridlogic.gridmap.at(coordinate).type = celltype::wall;
            }
        }
    }
}

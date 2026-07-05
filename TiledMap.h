#pragma once

#include "GridLogic.h"
#include "MissionStructs.h"
#include "TiledStructs.h"
#include <map>
#include <string>
#include <vector>

class TiledMap
{
public:
    int width = 0;
    int height = 0;
    int tileWidth = 32;
    int tileHeight = 32;

    TiledTileset tileset;
    std::vector<TiledLayer> layers;
    std::vector<TiledObjectLayer> objectLayers;
    std::map<int, TiledTileProperties> tileProperties;

    bool loadFromJson(const std::string& mapPath);
    bool loadTilesetFromTsx(const std::string& tilesetPath);
    void loadTilesetTexture(const std::string& texturePath);
    void unloadTextures() const;
    void draw(int startX, int startY) const;
    void draw(int startX, int startY, int renderTileSize) const;

    const TiledLayer* getLayerByName(const std::string& layerName) const;
    const TiledObjectLayer* getObjectLayerByName(const std::string& layerName) const;
    std::vector<DeploymentSlot> getDeploymentSlots(
        const std::string& layerName = "PlayerSpawners") const;
    std::vector<EncounterSpawn> getEncounterSpawns(
        const std::string& layerName = "EncounterSpawners") const;

    void initializeGrid(GridLogic& gridlogic, const std::string& blockedLayerName) const;
    void initializeGrid(GridLogic& gridlogic, const std::string& walkableLayerName, const std::string& blockedLayerName) const;
    void initializeGrid(
        GridLogic& gridlogic,
        const std::string& walkableLayerName,
        const std::string& blockedLayerName,
        const std::string& objectLayerName) const;
};

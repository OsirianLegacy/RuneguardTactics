#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

#include "UnitBase.h"

class UnitFactory
{
public:
    explicit UnitFactory(std::filesystem::path databaseDirectory = "Units/UnitDatabase");

    UnitBase BuildUnit(const std::string& id) const;

private:
    void LoadDefinitions();
    void LoadDefinitionFile(const std::filesystem::path& filePath);

    std::filesystem::path databaseDirectory;
    std::unordered_map<std::string, UnitDefinition> defs;
};

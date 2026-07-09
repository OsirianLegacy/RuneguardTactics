cmake_minimum_required(VERSION 3.15)
project(RuneguardTactics C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Link the MSVC runtime statically so the shipped build does not depend on the
# Visual C++ redistributable for this project or the bundled raylib build.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Build raylib as a static library from the local source tree.
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
add_subdirectory("../../raylib/raylib" raylib-build)

add_executable(RuneguardTactics RuneguardTactics.cpp
        GridStructs.h
        gridlogic.h
        gridlogic.cpp
        debugtools.h
        gridvisuals.cpp
        gridvisuals.h
        renderer.cpp
        renderer.h
        InputManager.cpp
        InputManager.h
        Colors.h
        CombatStructs.h
        CombatManager.h
        CombatManager.cpp
        Spawner.h
        Spawner.cpp
        TiledStructs.h
        TiledMap.h
        TiledMap.cpp
        Units/UnitBase.h
        Units/UnitBase.cpp
        Units/UnitFactory.h
        Units/UnitFactory.cpp
        Units/Stats/AP.h
        Units/Stats/AP.cpp
        Units/Stats/Damage.h
        Units/Stats/Damage.cpp
        Units/Stats/Defense.h
        Units/Stats/Defense.cpp
        Units/Stats/Healing.h
        Units/Stats/Healing.cpp
        Units/Stats/Health.h
        Units/Stats/Health.cpp
        Units/Stats/Movement.h
        Units/Stats/Movement.cpp
        Units/Stats/Range.h
        Units/Stats/Range.cpp
        Units/Stats/speed.h
        Units/Stats/speed.cpp
        Units/Stats/Stats.h
        Units/Stats/Stats.cpp
        Units/Stats/UnitDefinition.h
        MissionStructs.h
        GameState.cpp
        GameState.h
        GameEnums.h
        Roster.cpp
        Roster.h
        GameStructs.h
        Missions.h
        Missions.cpp
        GameUI.cpp
        GameUI.h
        GameEvents.cpp
        GameEvents.h
        MissionManager.cpp
        MissionManager.h
)
target_include_directories(RuneguardTactics PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty")
target_link_libraries(RuneguardTactics PRIVATE raylib)

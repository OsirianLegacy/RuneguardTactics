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
        debugtools.h)
target_link_libraries(RuneguardTactics PRIVATE raylib)

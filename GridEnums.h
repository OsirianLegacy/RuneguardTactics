#pragma once
#include <cstdint>
#include <string>
// used to set default walkable value
enum class celltype : std::uint8_t
{
    empty,
    ground,
    wall,
    water
};

inline std::string toString(const celltype type) {
    switch (type)
    {
        case celltype::empty:
            return "Empty";
        case celltype::ground:
            return "Ground";
        case celltype::wall:
            return "Wall";
        case celltype::water:
            return "Water";
        default: ;
    }

    return "Unknown";
};

// used in gridlogic map to map a neighbor to a specific cell lookup
enum class direction : std::uint8_t
{
    north,
    south,
    east,
    west,
    north_east,
    north_west,
    south_east,
    south_west
};
#include "gridlogic.h"
#include <iostream>
using namespace std;
gridlogic::gridlogic(const int width, const int height)
{
    gridlogic::gridwidth = width;
    gridlogic::gridheight = height;
}

std::map<coord, cell> gridlogic::generategrid(bool debuggrid){
    cout << "------ Generating Grid ------\n";
    for (int x = 0; x < gridwidth; ++x) {
        for (int y = 0; y < gridheight; ++y) {
            coord coordinate{x,y};
            cell cell;
            cell.coordinates = coordinate;
            gridmap.emplace(coordinate, cell);
        }
    }
    if (debuggrid)
    {
        debug();
    }

    cout << "------Grid Generation Complete------\n";
    return map<coord, cell>{};
}

void gridlogic::debug()
{
    for (const auto& [coord, cell] : gridmap)
    {
        cout << "coordinates: " << coord.x << "," << coord.y << "\n"
             << "walkable: " << cell.walkable << "\n"
             << "cost: " << cell.cost << "\n"
             << "type: " << toString(cell.type) << "\n";
    }
}

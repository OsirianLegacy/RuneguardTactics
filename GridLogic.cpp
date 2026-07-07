#include "GridLogic.h"

#include <array>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;
GridLogic::GridLogic(const int width, const int height)
{
    GridLogic::gridwidth = width;
    GridLogic::gridheight = height;
}

    void GridLogic::generategrid(bool debuggrid){
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
}

std::vector<coord> GridLogic::bfs(coord start, int depth, bool diagonals) const
{
    std::vector<coord> reachable;

    if (!gridmap.contains(start))
    {
        return reachable;
    }

    std::queue<coord> frontier;
    std::set<coord> visited;
    std::map<coord, int> distance;

    frontier.push(start);
    visited.insert(start);
    distance[start] = 0;

    while (!frontier.empty())
    {
        coord current = frontier.front();
        frontier.pop();

        reachable.push_back(current);

        for (coord neighbor : getCellNeighbors(current, diagonals))
        {
            if (visited.contains(neighbor))
            {
                continue;
            }

            int newDistance = distance[current] + 1;

            if (newDistance > depth)
            {
                continue;
            }

            visited.insert(neighbor);
            distance[neighbor] = newDistance;
            frontier.push(neighbor);
        }
    }

    return reachable;
}

std::vector<coord> GridLogic::getCellsInMovementRange(coord start, int movementRange, bool diagonals) const
{
    std::vector<coord> reachable;

    if (!gridmap.contains(start))
    {
        return reachable;
    }

    std::queue<coord> frontier;
    std::set<coord> visited;
    std::map<coord, int> distance;

    frontier.push(start);
    visited.insert(start);
    distance[start] = 0;

    while (!frontier.empty())
    {
        coord current = frontier.front();
        frontier.pop();

        reachable.push_back(current);

        for (coord neighbor : getCellNeighbors(current, diagonals))
        {
            if (visited.contains(neighbor))
            {
                continue;
            }

            const cell& neighborCell = gridmap.at(neighbor);

            if (!neighborCell.walkable)
            {
                continue;
            }

            if (neighborCell.occupied)
            {
                continue;
            }

            const int newDistance = distance[current] + neighborCell.cost;

            if (newDistance > movementRange)
            {
                continue;
            }

            visited.insert(neighbor);
            distance[neighbor] = newDistance;
            frontier.push(neighbor);
        }
    }

    return reachable;
}

std::vector<coord> GridLogic::getCellNeighbors(coord coordinate, bool diagonals) const
{
    std::vector<coord> neighbors = {};
    if (diagonals) {
        neighbors =
        {
            coord{coordinate.x + 1, coordinate.y},
            coord{coordinate.x - 1, coordinate.y},
            coord{coordinate.x, coordinate.y + 1},
            coord{coordinate.x, coordinate.y - 1},
            coord{coordinate.x + 1, coordinate.y + 1},
            coord{coordinate.x + 1, coordinate.y - 1},
            coord{coordinate.x - 1, coordinate.y + 1},
            coord{coordinate.x - 1, coordinate.y - 1}
        };
    }
    else {
        neighbors =
        {
            coord{coordinate.x + 1, coordinate.y},
            coord{coordinate.x - 1, coordinate.y},
            coord{coordinate.x, coordinate.y + 1},
            coord{coordinate.x, coordinate.y - 1},
        };
    }

    std::vector<coord> validneighbors = {};
    if (gridmap.contains(coordinate))
        {
        for (auto neighbor: neighbors)
            {
            coord neighbortocheck = {neighbor.x, neighbor.y};
            if (gridmap.contains(neighbortocheck))
            {
                validneighbors.push_back(neighbortocheck);
            }
        }
        return validneighbors;
    }
    else {
        std::cout << "coord to check for getCellNeighbors: " << coordinate.x << "," << coordinate.y << " does not exist in GridMap!" << std::endl;
        return validneighbors;
    }
}

void GridLogic::debug()
{
    for (const auto& [coord, cell] : gridmap)
    {
        cout << "coordinates: " << coord.x << "," << coord.y << "\n"
             << "walkable: " << cell.walkable << "\n"
             << "occupied: " << cell.occupied << "\n"
             << "cost: " << cell.cost << "\n"
             << "type: " << toString(cell.type) << "\n";
    }
}

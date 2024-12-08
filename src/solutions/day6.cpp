#include "../../include/day6.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <thread>

namespace
{
    struct pos
    {
        int x;
        int y;
    };

    struct tile
    {
        char tile;
        char orientation;
    };

    void clearConsole()
    {
#ifdef _WIN32
        system("cls"); // Windows
#else
        system("clear"); // Linux/macOS
#endif
    }

    std::vector<std::vector<tile>> getGrid()
    {
        std::ifstream file("./puzzleinputs/day6.txt");

        std::vector<std::vector<tile>> grid;
        std::string line;

        while (std::getline(file, line))
        {
            for (int i = 0; i < line.length(); i++)
            {
                if (i >= grid.size())
                {
                    grid.resize(i + 1);
                }
                if (grid[i].empty())
                {
                    grid[i] = {{line[i], 'i'}};
                }
                else
                {
                    grid[i].push_back({line[i], 'i'});
                }
            }
        }
        return grid;
    }

    char getNextRotation(char current)
    {
        std::vector<int> rotations = {'^', '>', 'v', '<'};
        for (size_t i = 0; i < rotations.size(); ++i)
        {
            if (rotations[i] == current)
            {
                return rotations[(i + 1) % rotations.size()];
            }
        }
        return current;
    }

    void move(std::vector<std::vector<tile>> &grid, pos &current, pos next, int &moves)
    {
        if (grid[next.x][next.y].tile == '#' || grid[next.x][next.y].tile == 'O')
        {
            grid[current.x][current.y].tile = getNextRotation(grid[current.x][current.y].tile);
            return;
        }

        if (grid[next.x][next.y].tile != 'X')
        {
            grid[next.x][next.y].tile = 'X';
            moves++;
        }

        grid[next.x][next.y].orientation = grid[current.x][current.y].tile;

        std::swap(grid[current.x][current.y], grid[next.x][next.y]);
        current.x = next.x;
        current.y = next.y;
    }

    void print(std::vector<std::vector<tile>> &grid)
    {
        clearConsole();

        for (int y = 0; y < grid[0].size(); y++)
        {
            for (int x = 0; x < grid.size(); x++)
            {
                std::cout << grid[x][y].tile;
            }
            std::cout << '\n';
        }

        std::cout << '\n';
        std::cout << '\n';
    }

    pos getGuardPosition(std::vector<std::vector<tile>> &grid)
    {
        pos current;
        for (int y = 0; y < grid[0].size(); y++)
        {
            for (int x = 0; x < grid.size(); x++)
            {
                if (grid[x][y].tile == '^')
                {
                    current.x = x;
                    current.y = y;
                }
            }
        }
        return current;
    }

    bool tryEscapeLevel(std::vector<std::vector<tile>> &grid, bool partOne)
    {
        pos current = getGuardPosition(grid);
        int moves = 1;
        while (true)
        {
            pos next;

            if (grid[current.x][current.y].tile == '^')
            {
                next = {current.x, current.y - 1};
            }

            else if (grid[current.x][current.y].tile == '>')
            {
                next = {current.x + 1, current.y};
            }

            else if (grid[current.x][current.y].tile == 'v')
            {
                next = {current.x, current.y + 1};
            }

            else if (grid[current.x][current.y].tile == '<')
            {
                next = {current.x - 1, current.y};
            }

            if (next.x >= grid.size() || next.x < 0 || next.y >= grid[0].size() || next.y < 0)
            {
                break;
            }

            if (!partOne && grid[next.x][next.y].tile == 'X' && grid[current.x][current.y].tile == grid[next.x][next.y].orientation)
            {
                return false;
            }

            move(grid, current, next, moves);
        }
        if (partOne)
        {
            std::cout << "moves: " << moves << '\n';
        }
        return true;
    }
}
void Day6::SolvePartOne()
{
    auto grid = getGrid();
    tryEscapeLevel(grid, true);
}

void Day6::SolvePartTwo()
{
    auto grid = getGrid();
    pos start = getGuardPosition(grid);
    auto reachableLevelsGrid = grid;

    if(!tryEscapeLevel(reachableLevelsGrid, true)){
        std::cout << "cannot escape level to begin with" << '\n';
        return;
    }

    int goodObstacleCount = 1; // set to 1 because there could be an obstacle at level escape tile.
    for (int y = 0; y < reachableLevelsGrid[0].size(); y++)
    {
        for (int x = 0; x < reachableLevelsGrid.size(); x++)
        {
            if (reachableLevelsGrid[x][y].tile == 'X' && !(x == start.x && y == start.y))
            {
                auto newGrid = grid;
                newGrid[x][y].tile = 'O';

                if (!tryEscapeLevel(newGrid, false))
                {
                    // std::cout << "obstacle count: " << goodObstacleCount << '\n';
                    goodObstacleCount++;
                }
                if(goodObstacleCount == 64){
                    print(newGrid);
                    return;
                }
            }
        }
    }
    std::cout << "result: " << goodObstacleCount << '\n';
}

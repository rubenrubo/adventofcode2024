#include "../../include/day8.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

namespace
{
    struct pos
    {
        int x;
        int y;
    };

    struct antenna
    {
        char frequency;
        pos pos;
    };

    std::vector<std::vector<char>> getGrid()
    {
        std::ifstream file("./puzzleinputs/day8.txt");

        std::vector<std::vector<char>> grid;
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
                    grid[i] = {line[i]};
                }
                else
                {
                    grid[i].push_back(line[i]);
                }
            }
        }
        return grid;
    }

    std::vector<antenna> getAntennas(std::vector<std::vector<char>> &grid)
    {
        std::vector<antenna> result;
        for (int y = 0; y < grid[0].size(); y++)
        {
            for (int x = 0; x < grid.size(); x++)
            {
                if (grid[x][y] != '.')
                {
                    result.push_back({grid[x][y], {x, y}});
                }
            }
        }
        return result;
    }

    void print(std::vector<std::vector<char>> &grid)
    {
        for (int y = 0; y < grid[0].size(); y++)
        {
            for (int x = 0; x < grid.size(); x++)
            {
                std::cout << grid[x][y];
            }
            std::cout << '\n';
        }
        std::cout << '\n';
        std::cout << '\n';
    }
}

void Day8::SolvePartOne()
{
    auto grid = getGrid();
    auto antennas = getAntennas(grid);

    int antiNodes = 0;
    for (auto antenna : antennas)
    {
        for (auto otherAntenna : antennas)
        {
            if (otherAntenna.pos.x == antenna.pos.x && otherAntenna.pos.y == antenna.pos.y || antenna.frequency != otherAntenna.frequency)
            {
                continue;
            }

            int antiNodeX = antenna.pos.x + (antenna.pos.x - otherAntenna.pos.x);
            int antiNodeY = antenna.pos.y + (antenna.pos.y - otherAntenna.pos.y);

            if (antiNodeX >= grid.size() || antiNodeX < 0 || antiNodeY >= grid[0].size() || antiNodeY < 0)
            {
                continue;
            }

            if (grid[antiNodeX][antiNodeY] != '#')
            {
                grid[antiNodeX][antiNodeY] = '#';
                antiNodes++;
            }
        }
    }
    print(grid);
    std::cout << "Result: " << antiNodes << '\n';
}

void Day8::SolvePartTwo()
{
    auto grid = getGrid();
    auto antennas = getAntennas(grid);

    int antiNodes = 0;
    for (auto antenna : antennas)
    {
        for (auto otherAntenna : antennas)
        {
            if (otherAntenna.pos.x == antenna.pos.x && otherAntenna.pos.y == antenna.pos.y || antenna.frequency != otherAntenna.frequency)
            {
                continue;
            }

            int antiNodeX = antenna.pos.x + (antenna.pos.x - otherAntenna.pos.x);
            int antiNodeY = antenna.pos.y + (antenna.pos.y - otherAntenna.pos.y);

            while (!(antiNodeX >= grid.size() || antiNodeX < 0 || antiNodeY >= grid[0].size() || antiNodeY < 0))
            {
                if (grid[antiNodeX][antiNodeY] == '.')
                {
                    grid[antiNodeX][antiNodeY] = '#';
                    antiNodes++;
                }
                antiNodeX += antenna.pos.x - otherAntenna.pos.x;
                antiNodeY += antenna.pos.y - otherAntenna.pos.y;
            }
        }
    }
    print(grid);
    std::cout << "Result: " << antiNodes + antennas.size() << '\n';
}

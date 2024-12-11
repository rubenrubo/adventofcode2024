#include "../../include/day10.h"
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

    std::vector<std::vector<char>> getGrid()
    {
        std::ifstream file("./puzzleinputs/day10.txt");

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

    void traverse(std::vector<std::vector<char>> &grid, pos cur, int &result, std::map<std::string, int> &visitedTrailEnds)
    {
        if (grid[cur.x][cur.y] == '9')
        {
            std::string key = std::to_string(cur.x) + "," + std::to_string(cur.y);

            if (visitedTrailEnds.count(key) > 0)
            {
                visitedTrailEnds[key] += 1;
                return;
            }
            else
            {
                result++;
                visitedTrailEnds[key] = 1;
                return;
            }
        }

        int height = grid[cur.x][cur.y] - 48;

        if (cur.x + 1 < grid.size() && (grid[cur.x + 1][cur.y] - '0') == height + 1)
            traverse(grid, {cur.x + 1, cur.y}, result, visitedTrailEnds);

        if (cur.y + 1 < grid[0].size() && (grid[cur.x][cur.y + 1] - '0') == height + 1)
            traverse(grid, {cur.x, cur.y + 1}, result, visitedTrailEnds);

        if (cur.x - 1 >= 0 && (grid[cur.x - 1][cur.y] - '0') == height + 1)
            traverse(grid, {cur.x - 1, cur.y}, result, visitedTrailEnds);

        if (cur.y - 1 >= 0 && (grid[cur.x][cur.y - 1] - '0') == height + 1)
            traverse(grid, {cur.x, cur.y - 1}, result, visitedTrailEnds);
    }

    std::vector<pos> GetStartingPositions(std::vector<std::vector<char>> &grid)
    {
        std::vector<pos> result;
        for (int y = 0; y < grid[0].size(); y++)
        {
            for (int x = 0; x < grid.size(); x++)
            {
                if (grid[x][y] - '0' == 0)
                {
                    result.push_back({x, y});
                }
            }
        }
        return result;
    }
}

void Day10::Solve()
{
    auto grid = getGrid();
    int resultPartOne = 0;
    int resultPartTwo = 0;
    auto start = GetStartingPositions(grid);
    for (auto location : start)
    {
        std::map<std::string, int> visitedTrailEnds;
        traverse(grid, location, resultPartOne, visitedTrailEnds);
        for (const auto &pair : visitedTrailEnds)
        {
            resultPartTwo += pair.second;
        }
    }
    std::cout << "Result part one: " << resultPartOne << '\n';
    std::cout << "Result part two: " << resultPartTwo << '\n';
}
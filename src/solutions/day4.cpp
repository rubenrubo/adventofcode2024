#include "../../include/day4.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

void Day4::SolvePartOne()
{
    auto grid = getGrid();

    int xmasCount = 0;
    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid[y].size(); x++)
        {
            std::vector<std::string> words;

            // left to right
            words.push_back(std::string() + getChar(grid, x, y) + getChar(grid, x + 1, y) + getChar(grid, x + 2, y) + getChar(grid, x + 3, y));

            // top to bottom
            words.push_back(std::string() + getChar(grid, x, y) + getChar(grid, x, y + 1) + getChar(grid, x, y + 2) + getChar(grid, x, y + 3));

            // diagonal top to bottom right
            words.push_back(std::string() + getChar(grid, x, y) + getChar(grid, x + 1, y + 1) + getChar(grid, x + 2, y + 2) + getChar(grid, x + 3, y + 3));

            // diagonal bottom to top right
            words.push_back(std::string() + getChar(grid, x, y) + getChar(grid, x + 1, y - 1) + getChar(grid, x + 2, y - 2) + getChar(grid, x + 3, y - 3));

            for (std::string word : words){
                if(word == "XMAS" || word == "SAMX"){
                    xmasCount++;
                }
            }
        }
    }
    std::cout << "xmas counter: " << xmasCount;
}

void Day4::SolvePartTwo()
{
    auto grid = getGrid();

    int xmasCount = 0;
    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid[y].size(); x++)
        {
            // top left to bottom right
            auto word = std::string() + getChar(grid, x, y) + getChar(grid, x + 1, y + 1) + getChar(grid, x + 2, y + 2);
            // top right to bottom left
            auto word1 = std::string() + getChar(grid, x + 2, y) + getChar(grid, x + 1, y + 1) + getChar(grid, x, y + 2);

            if((word == "MAS" || word == "SAM") && (word1 == "MAS" || word1 == "SAM")){
                xmasCount++;
            }
        }
    }
    std::cout << "xmas counter: " << xmasCount;
}

char Day4::getChar(const std::vector<std::vector<char>> &grid, int x, int y)
{
    if (x >= 0 && x < grid.size() && y >= 0 && y < grid[x].size())
    {
        return grid[x][y];
    }
    return '.';
}

std::vector<std::vector<char>> Day4::getGrid(){
std::ifstream file("./puzzleinputs/day4.txt");

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
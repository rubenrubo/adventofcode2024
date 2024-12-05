#include "../../include/day5.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

namespace
{
    std::unordered_map<int, std::vector<int>> GetRules()
    {
        std::ifstream file("./puzzleinputs/day5rules.txt");
        std::unordered_map<int, std::vector<int>> map;
        std::ostringstream buffer;
        buffer << file.rdbuf();
        std::regex pattern(R"((\d+)\|(\d+))");
        std::string input = buffer.str();

        auto matches_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
        auto matches_end = std::sregex_iterator();
        for (std::sregex_iterator i = matches_begin; i != matches_end; ++i)
        {
            std::smatch match = *i;

            int num1 = std::stoi(match[1].str());
            int num2 = std::stoi(match[2].str());

            if (map[num1].empty())
            {
                map[num1] = {num2};
            }
            else
            {
                map[num1].push_back(num2);
            }
        }
        return map;
    }

    std::vector<std::vector<int>> GetPageNumbers()
    {
        std::ifstream file("./puzzleinputs/day5updates.txt");
        std::string line;
        std::regex pattern(R"((\d+))");
        std::vector<std::vector<int>> result;

        int counter = 0;
        while (std::getline(file, line))
        {
            result.resize(counter + 1);

            auto matches_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
            auto matches_end = std::sregex_iterator();
            for (std::sregex_iterator i = matches_begin; i != matches_end; ++i)
            {
                std::smatch match = *i;
                int num = std::stoi(match[1].str());
                result[counter].push_back(num);
            }
            counter++;
        }
        return result;
    }

    bool hasValue(const std::unordered_map<int, std::vector<int>> &map, int key, int value)
    {
        auto it = map.find(key);
        if (it != map.end())
        {                                                                 // Check if the key exists
            const auto &vec = it->second;                                 // Get the vector associated with the key
            return std::find(vec.begin(), vec.end(), value) != vec.end(); // Check if value exists in vector
        }
        return false; // Key doesn't exist
    }
}

void Day5::SolvePartOne()
{
    auto rulesMap = GetRules();
    auto pageNumbers = GetPageNumbers();

    int result = 0;
    for (auto update : pageNumbers)
    {
        bool valid = true;
        for (int i = 0; i < update.size(); i++)
        {
            for (int next = i + 1; next < update.size(); next++)
            {
                if (!hasValue(rulesMap, update[i], update[next]))
                {
                    valid = false;
                }
            }
        }
        if (valid)
        {
            int middleIndex = (update.size() - 1) / 2;
            result += update[middleIndex];
        }
    }
    std::cout << "result: " << result << std::endl;
}

void Day5::SolvePartTwo()
{
    auto rulesMap = GetRules();
    auto pageNumbers = GetPageNumbers();

    int result = 0;
    for (auto update : pageNumbers)
    {
        bool invalid = true;
        bool hasSwapped = false;
        while (invalid)
        {
            bool invalidOccurance = false;
            for (int i = 0; i < update.size(); i++)
            {
                for (int next = i + 1; next < update.size(); next++)
                {
                    if (!hasValue(rulesMap, update[i], update[next]))
                    {
                        std::iter_swap(update.begin() + i, update.begin() + next);
                        invalidOccurance = true;
                        hasSwapped = true;
                    }
                }
            }
            if (!invalidOccurance)
            {
                invalid = false;
                if (hasSwapped)
                {
                    int middleIndex = (update.size() - 1) / 2;
                    result += update[middleIndex];
                }
            }
        }
    }
    std::cout << "result: " << result << std::endl;
}

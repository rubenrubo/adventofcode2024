#include "../../include/day3.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

void Day3::SolvePartOne()
{
    std::ifstream file("./puzzleinputs/day3.txt");

    std::ostringstream buffer;
    buffer << file.rdbuf(); 

    std::string input = buffer.str();

    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    auto matches_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto matches_end = std::sregex_iterator();

    int result = 0;
    for (std::sregex_iterator i = matches_begin; i != matches_end; ++i)
    {
        std::smatch match = *i;

        int num1 = std::stoi(match[1].str()); 
        int num2 = std::stoi(match[2].str());
        result += (num1 * num2);
    }
    std::cout << "total result: " << result;
}

void Day3::SolvePartTwo()
{
    std::ifstream file("./puzzleinputs/day3.txt");

    std::ostringstream buffer;
    buffer << file.rdbuf(); 

    std::string input = buffer.str();

    std::regex pattern(R"(mul\((\d+),(\d+)\)|don't\(\)|do\(\))");

    auto matches_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto matches_end = std::sregex_iterator();
    int result = 0;
    bool multiply = true;
    for (std::sregex_iterator i = matches_begin; i != matches_end; ++i)
    {
        std::smatch match = *i;

        if (match[0] == "do()")
        {
            multiply = true;
            continue;
        }

        if (match[0] == "don't()")
        {
            multiply = false;
            continue;
        }

        if (multiply)
        {
            int num1 = std::stoi(match[1].str()); 
            int num2 = std::stoi(match[2].str());
            result += (num1 * num2);
        }
    }
    std::cout << "total result: " << result;
}
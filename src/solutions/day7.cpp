#include "../../include/day7.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <algorithm>
#include <cstdint>

namespace
{
    // use uint64_t which apparently is equivalent to long long. This is required for one of the last inputs that contains a 15 digit number.
    struct equation
    {
        uint64_t testValue;
        std::vector<uint64_t> numbers;
    };

    std::vector<equation> getEquations()
    {
        std::ifstream file("./puzzleinputs/day7.txt");

        std::vector<equation> equations;
        std::string line;

        while (std::getline(file, line))
        {
            equation eq;
            eq.testValue = std::stoll(line.substr(0, line.find(':')));
            std::stringstream ss(line.substr(line.find(':') + 2));
            std::string str;
            while (std::getline(ss, str, ' '))
            {
                eq.numbers.push_back(std::stoll(str));
            }
            equations.push_back(eq);
        }
        return equations;
    }

    uint64_t concat(uint64_t numb1, uint64_t numb2)
    {
        return std::stoll(std::to_string(numb1) + std::to_string(numb2));
    }

    bool validEquation(equation &eq, uint64_t operationsResult, int nextNumIndex)
    {
        if (nextNumIndex == eq.numbers.size())
        {
            return eq.testValue == operationsResult;
        }

        return validEquation(eq, operationsResult + eq.numbers[nextNumIndex], nextNumIndex + 1) ||
               validEquation(eq, operationsResult * eq.numbers[nextNumIndex], nextNumIndex + 1);
    }

    bool validEquationP2(equation &eq, uint64_t operationsResult, int nextNumIndex)
    {
        if (nextNumIndex == eq.numbers.size())
        {
            return eq.testValue == operationsResult;
        }

        return validEquationP2(eq, operationsResult + eq.numbers[nextNumIndex], nextNumIndex + 1) ||
               validEquationP2(eq, operationsResult * eq.numbers[nextNumIndex], nextNumIndex + 1) ||
               validEquationP2(eq, concat(operationsResult, eq.numbers[nextNumIndex]), nextNumIndex + 1);
    }
}

void Day7::SolvePartOne()
{
    auto equations = getEquations();
    uint64_t result = 0;
    for (auto eq : equations)
    {
        if (validEquation(eq, eq.numbers.front(), 1))
        {
            result += eq.testValue;
        }
    }
    std::cout << "Result: " << result;
}

void Day7::SolvePartTwo()
{
    auto equations = getEquations();
    uint64_t result = 0;
    for (auto eq : equations)
    {
        if (validEquationP2(eq, eq.numbers.front(), 1))
        {
            result += eq.testValue;
        }
    }
    std::cout << "Result: " << result;
}

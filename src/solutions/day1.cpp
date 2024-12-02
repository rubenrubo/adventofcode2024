#include "../../include/day1.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm> // Include for std::max
#include <sstream>

void Day1::SolvePartOne()
{
    // input filestream object named File
    std::ifstream file("./puzzleinputs/day1.txt");

    std::vector<int> firstColumn;  // Vector for the first column
    std::vector<int> secondColumn; // Vector for the second column
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line); // Create a string stream from the line
        int first, second;

        // Read the two integers from the line
        if (iss >> first >> second)
        {
            firstColumn.push_back(first);   // Store the first digit
            secondColumn.push_back(second); // Store the second digit
        }
    }

    std::sort(firstColumn.begin(), firstColumn.end());
    std::sort(secondColumn.begin(), secondColumn.end());
    size_t size = firstColumn.size(); // Get the number of elements
    int result = 0;

    for (size_t i = 0; i < size; i++)
    {
        int difference = std::abs(firstColumn[i] - secondColumn[i]);
        result += difference; // Accumulate the positive differences
    }

    std::cout << "Total result: " << result << std::endl;
}

void Day1::SolvePartTwo()
{
    // input filestream object named File
    std::ifstream file("./puzzleinputs/day1.txt");

    std::vector<int> firstColumn;  // Vector for the first column
    std::vector<int> secondColumn; // Vector for the second column
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line); // Create a string stream from the line
        int first, second;

        // Read the two integers from the line
        if (iss >> first >> second)
        {
            firstColumn.push_back(first);   // Store the first digit
            secondColumn.push_back(second); // Store the second digit
        }
    }

    size_t size = firstColumn.size(); // Get the number of elements
    int result = 0;

    for (size_t i = 0; i < size; i++)
    {
        int occurrences = countOccurrences(secondColumn, size, firstColumn[i]);
        result += firstColumn[i] * occurrences;
    }

    std::cout << "Total result: " << result << std::endl;
}

int Day1::countOccurrences(std::vector<int> arr, int size, int target)
{
    int count = 0; // Initialize counter to zero
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            count++; // Increment count if the current element matches the target
        }
    }
    return count; // Return the total count
}
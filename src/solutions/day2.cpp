#include "../../include/day2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>

void Day2::SolvePartOne()
{
    auto reports = GetReports();

    int safeReports = 0;
    for (std::vector<int> report : reports)
    {
        if (ReportIsValid(report))
        {
            safeReports++;
        }
    }

    std::cout << "Safe reports: " << safeReports << std::endl;
}

void Day2::SolvePartTwo()
{
    auto reports = GetReports();
    int safeReports = 0;
    for (std::vector<int> report : reports)
    {
        if (ReportIsValid(report))
        {
            safeReports++;
            continue;
        }

        size_t size = report.size();

        for (size_t i = 0; i <= size - 1; i++)
        {
            std::vector<int> clonedReport = report;
            clonedReport.erase(clonedReport.begin() + i);
            if (ReportIsValid(clonedReport))
            {
                safeReports++;
                break;
            }
        }
    }

    std::cout << "Safe reports: " << safeReports << std::endl;
}

std::vector<std::vector<int>> Day2::GetReports()
{
    std::ifstream file("./puzzleinputs/day2.txt");

    std::vector<std::vector<int>> reports;
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        int level;

        std::vector<int> report;

        while (iss >> level)
        {
            report.push_back(level);
        }
        reports.push_back(report);
    }
    return reports;
}

bool Day2::ReportIsValid(std::vector<int> report)
{
    bool descending = report[0] > report[1];
    bool valid = true;

    size_t size = report.size();

    for (size_t i = 0; i < size - 1; i++)
    {
        if ((descending && report[i] < report[i + 1]) || (!descending && report[i] > report[i + 1]))
        {
            valid = false;
            break;
        }

        int difference = std::abs(report[i] - report[i + 1]);

        if (difference == 0 || difference > 3)
        {
            valid = false;
            break;
        }
    }
    return valid;
}

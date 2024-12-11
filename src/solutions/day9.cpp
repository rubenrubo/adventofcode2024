#include "../../include/day9.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdint>

namespace
{
    struct section
    {
        int start;
        int end;
    };

    void printBlocks(std::vector<int> &blocks)
    {
        for (auto block : blocks)
        {
            if (block == -1)
            {
                std::cout << '.';
                continue;
            }
            std::cout << block;
        }
        std::cout << '\n';
    }
    std::vector<int> GetBlocks(std::string input)
    {
        std::vector<int> result;
        int idNumber = 0;
        for (int i = 0; i < input.length(); i++)
        {
            int number = input[i] - 48;

            bool even = i % 2 == 0;

            if (even)
            {
                for (int i = 0; i < number; i++)
                {
                    result.push_back(idNumber);
                }
                idNumber++;
                continue;
            }

            for (int i = 0; i < number; i++)
            {
                result.push_back(-1);
            }
        }
        return result;
    }

    void Fragment(std::vector<int> &disk)
    {
        for (int i = 0; i < disk.size(); i++)
        {
            if (disk[i] != -1)
            {
                continue;
            }
            for (int endI = disk.size() - 1; endI >= 0; endI--)
            {
                if (endI < i)
                {
                    return;
                }
                if (disk[endI] == -1)
                {
                    continue;
                }
                std::iter_swap(disk.begin() + i, disk.begin() + endI);
                break;
            }
        }
    }

    void SwapSections(std::vector<int> &disk, section section1, section section2){
        for(int i = 0; i < (section1.end - section1.start + 1); i++){
            std::iter_swap(disk.begin() + section1.start + i, disk.begin() + section2.start + i);
        }
    }

    section GetFreeSection(std::vector<int> &disk, section section)
    {
        int requiredSpace = section.end - section.start + 1;
        int freeSpace = 0;
        for (int i = 0; i < disk.size(); i++)
        {
            if (disk[i] == -1)
            {
                freeSpace++;
            }
            else
            {
                freeSpace = 0;
            }
            if (freeSpace == requiredSpace)
            {
                return {i - requiredSpace + 1, i};
            }
        }
        return {-1, -1};
    }

    void FragmentP2(std::vector<int> &disk)
    {
        int currentId = disk[disk.size() - 1];
        int endIndex = disk.size() - 1;
        for (int i = disk.size() - 2; i >= 0; i--)
        {
            if(disk[i] != currentId){
                if(currentId != -1){
                    // get section and free section and try swap
                    section sectionToMove = {i+1, endIndex};
                    section freeSection = GetFreeSection(disk, sectionToMove);
                    if(freeSection.start != -1 && freeSection.end != -1 && freeSection.start < sectionToMove.start){
                        SwapSections(disk, sectionToMove, freeSection);
                    }
                }
                currentId = disk[i];
                endIndex = i;
            }
        }
    }

    uint64_t GetCheckSum(std::vector<int> &disk)
    {
        uint64_t checkSum = 0;
        for (int i = 0; i < disk.size(); i++)
        {
            if (disk[i] == -1)
            {
                continue;
            }
            checkSum += i * disk[i];
        }
        return checkSum;
    }
}

void Day9::SolvePartOne()
{
    std::ifstream file("./puzzleinputs/day9.txt");
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    auto blocks = GetBlocks(input);
    Fragment(blocks);
    std::cout << "result: " << GetCheckSum(blocks);
}

void Day9::SolvePartTwo()
{
    std::ifstream file("./puzzleinputs/day9.txt");
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    auto blocks = GetBlocks(input);
    FragmentP2(blocks);
    std::cout << "result: " << GetCheckSum(blocks);
}

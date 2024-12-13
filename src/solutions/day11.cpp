#include "../../include/day11.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <map>

namespace
{
  void Solve(int blinks)
  {
    std::map<uint64_t, uint64_t> stones = {{7725, 1}, {185, 1}, {2, 1}, {132869, 1}, {0, 1}, {1840437, 1}, {62, 1}, {26310, 1}};

    for (int blink = 0; blink < blinks; blink++)
    {
      std::map<uint64_t, uint64_t> newStones;
      for (const auto &stone : stones)
      {
        if (stone.first == 0)
        {
          newStones[1] = stones[0];
          continue;
        }

        auto stoneString = std::to_string(stone.first);
        if (stoneString.length() % 2 == 0)
        {
          auto split = std::stoll(stoneString.substr(0, stoneString.length() / 2));
          auto split2 = std::stoll(stoneString.substr(stoneString.length() / 2));

          newStones[split] += stones[stone.first];
          newStones[split2] += stones[stone.first];
          continue;
        }
        newStones[stone.first * 2024] = stones[stone.first];
      }
      stones = newStones;
    }

    uint64_t result = 0;
    for (const auto &stone : stones)
    {
      if (stone.second > 0)
      {
        result += stone.second;
      }
    }

    std::cout << "Result: " << result << '\n';
  }
}

void Day11::SolvePartOne()
{
  Solve(25);
}

void Day11::SolvePartTwo()
{
    Solve(75);
}

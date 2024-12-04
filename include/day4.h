#include <vector>

class Day4
{
public:
    void SolvePartOne();
    void SolvePartTwo();

private:
    char getChar(const std::vector<std::vector<char>> &grid, int x, int y);
    std::vector<std::vector<char>> getGrid();
};
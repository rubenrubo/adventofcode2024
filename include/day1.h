#include <vector> // Include for std::vector

class Day1
{
public:
    void SolvePartOne();
    void SolvePartTwo();

private:
    int countOccurrences(std::vector<int> arr, int size, int target);
};
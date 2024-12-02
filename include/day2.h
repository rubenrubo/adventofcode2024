#include <vector>

class Day2
{
public:
    void SolvePartOne();
    void SolvePartTwo();
private: 
    bool ReportIsValid(std::vector<int> report);
    std::vector<std::vector<int>> GetReports(); 
};
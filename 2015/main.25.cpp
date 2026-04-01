#include <cassert>
#include <vector>
#include <iostream>

using CodeMap = std::vector<std::vector<unsigned long long>>;

constexpr unsigned long long calculateNextCode(unsigned long long currentCode)
{
    const auto newVal = currentCode * 252533;
    return newVal % 33554393;
}

int main()
{
    constexpr std::pair<int, int> codePosition {2978-1, 3083-1};

    // row then col
    CodeMap currentCodes = {{20151125}};

    static_assert(calculateNextCode(20151125) == 31916031);

    std::pair<int, int> currentPosition {0,0};

    while (currentPosition != codePosition)
    {
        const auto nextCode = calculateNextCode(currentCodes[currentPosition.first][currentPosition.second]);

        if (currentPosition.first == 0)
        {
            currentCodes.push_back({nextCode});
            currentPosition = std::make_pair(currentCodes.size()-1, 0);
        }
        else
        {
            currentPosition.first--;
            currentCodes[currentPosition.first].push_back(nextCode);
            currentPosition.second++;
        }
    }

    assert(currentCodes[codePosition.first][codePosition.second] == 2650453);
    std::cout << currentCodes[codePosition.first][codePosition.second] << "\n";

    return 0;
}
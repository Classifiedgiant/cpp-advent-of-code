#include <algorithm>
#include <cassert>
#include <bitset>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

using Packages = std::vector<int>;

unsigned long minQuantumEntanglement(const Packages& packages, int val)
{
    const auto sz = packages.size();

    bool foundGroup = false;
    auto min = std::numeric_limits<unsigned long>::max();

    for(int bitCount{1}; !foundGroup; bitCount++)
    {
        std::vector<bool> bitMask(sz, false);
        std::fill_n(bitMask.begin(), bitCount, true);

        do
        {
            int sum{};
            unsigned long quantumEntanglement{1};

            for (const auto& [i, package] : packages | std::views::enumerate)
            {
                if (bitMask[i])
                {
                    sum += package;
                    quantumEntanglement *= package;
                }
            }

            if (sum == val)
            {
                min = std::min(min, quantumEntanglement);
                foundGroup = true;
            }

        } while (std::ranges::next_permutation(bitMask, std::greater()).found);
    }

    return min;

}

int main()
{
    std::vector packages {
        1,
        3,
        5,
        11,
        13,
        17,
        19,
        23,
        29,
        31,
        41,
        43,
        47,
        53,
        59,
        61,
        67,
        71,
        73,
        79,
        83,
        89,
        97,
        101,
        103,
        107,
        109,
        113
    }; // input

    auto sum = std::accumulate(packages.begin(), packages.end(), 0);

    const auto part1Ans = minQuantumEntanglement(packages, sum / 3);
    assert(part1Ans == 11266889531);

    const auto part2Ans = minQuantumEntanglement(packages, sum / 4);
    assert(part2Ans == 77387711);

    std::cout << part1Ans << " " << part2Ans << std::endl;

    return 0;
}

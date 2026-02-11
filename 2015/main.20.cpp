#include <algorithm>
#include <cassert>
#include <print>
#include <vector>

constexpr int input {34000000};
using HouseArray = std::vector<size_t>;

void GiveAllPresentToHouses(HouseArray& houses, size_t multiplier, size_t visits = 0)
{
    for (size_t elf{1}; elf < houses.size(); elf++)
    {
        const auto maxVisit = visits != 0 ? std::min(houses.size(), elf * visits) : houses.size();
        for (size_t elfStep{elf}; elfStep < maxVisit; elfStep+=elf)
        {
            houses[elfStep] += elf * multiplier;
        }
    }
}

int main()
{
    
    HouseArray houses(input/10, 0);
    GiveAllPresentToHouses(houses, 10);

    const auto predicate = [](const auto& elem)
    {
        return elem > input;
    };

    auto iter = std::find_if(begin(houses), end(houses), predicate);


    const auto part1Ans{std::distance(begin(houses), iter)};
    assert(part1Ans == 786240);

    std::fill(begin(houses), end(houses), 0);
    GiveAllPresentToHouses(houses, 11, 50);

    iter = std::find_if(begin(houses), end(houses), predicate);

    const auto part2Ans{std::distance(begin(houses), iter)};
    assert(part2Ans == 831600);

    std::println("{}, {}", part1Ans, part2Ans);
}
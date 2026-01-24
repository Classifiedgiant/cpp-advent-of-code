#include <algorithm>
#include <cassert>
#include <fstream>
#include <vector>
#include <print>
#include <string>
#include <ranges>

using Grid = std::array<std::array<bool, 100>, 100>;

void fillGridFromFile(Grid& grid, std::ifstream& file) {
    if (!file.is_open())
        throw std::runtime_error("File not found");

    std::string line;
    int row {};
    while (getline(file, line)) {
        int col {};
        for (const auto elem : line ) {
            grid[row][col++] = elem == '#';

        }
        row++;
    }
}

Grid calculateStep(const Grid& grid) {
    Grid newGrid{};

    constexpr std::array<std::pair<int, int>, 8> directions {{
        {-1,-1},
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0, 1},
        {1, -1},
        {1, 0},
        {1, 1}
    }};

    for (int row {}; row < grid.size(); row++) {
        for (int col {}; col < grid[0].size(); col++) {
            int lights {};
            for (const auto [dirRow, dirCol]: directions) {
                const auto newRow{dirRow + row};
                const auto newCol{dirCol + col};
                if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size() && grid[newRow][newCol])
                    lights++;
            }

            if (grid[row][col]) {
                newGrid[row][col] = lights == 2 or lights == 3;
            } else {
                newGrid[row][col] = lights == 3;
            }
        }
    }

    return newGrid;
}

void turnCornerLightsOn(Grid& grid) {
    grid[0][0] = true;
    grid[grid.size()-1][0] = true;
    grid[0][grid.size()-1] = true;
    grid[grid.size()-1][grid.size()-1] = true;
}

int main(int argc, const char* argv[]) {
    std::ifstream file{"./2015/18.txt"};

    Grid grid;
    fillGridFromFile(grid, file);

    constexpr int steps {100};
    Grid original = grid;
    for ([[maybe_unused]] auto _ : std::views::iota(0, steps)) {
        grid = calculateStep(grid);
    }

    const auto part1Ans = std::ranges::count( grid | std::views::join, true);
    assert(part1Ans == 821);

    grid = original;
    turnCornerLightsOn(grid);

    for ([[maybe_unused]] auto _ : std::views::iota(0, steps)) {
        grid = calculateStep(grid);
        turnCornerLightsOn(grid);
    }

    const auto part2Ans = std::ranges::count(grid | std::views::join, true );
    assert (part2Ans == 886);

    std::println("{} {}", part1Ans, part2Ans);
    return 0;
}

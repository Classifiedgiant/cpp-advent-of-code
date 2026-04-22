#include <cassert>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <set>
#include <string>
#include <utility>

#include "string_util.h"

using Position = std::pair<int, int>;

enum class Direction : int
{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

std::vector<std::string> getMoves(std::filesystem::path filePath)
{
    std::ifstream file {filePath.string()};

    std::string line{};
    std::getline(file, line);

    auto moves = Shared::SplitLine(line, ',');

    std::for_each(begin(moves), end(moves), [](auto& elem) {
        std::erase(elem, ' ');
    });

    return moves;
}

Direction calculateNewDirection(char turn, Direction currDir)
{
    if (turn == 'L')
        return static_cast<Direction>((static_cast<int>(currDir)+3) % 4);
    else if (turn == 'R')
        return static_cast<Direction>((static_cast<int>(currDir)+1) % 4);
    else
        return currDir;
}

void moveToNextSpot(Position& currPos, Direction& direction, std::string_view move)
{
    direction = calculateNewDirection(move[0], direction);

    int steps{};
    std::from_chars(move.data()+1, move.data()+move.size(), steps);

    switch (direction)
    {
        case Direction::NORTH:
            currPos.second += steps;
        break;

        case Direction::EAST:
            currPos.first += steps;
        break;

        case Direction::SOUTH:
            currPos.second -= steps;
        break;

        case Direction::WEST:
            currPos.first -= steps;
        break;
    };
}

std::optional<Position> moveToNextSpotIncrementally(Position& currPos, Direction& direction, std::string_view move, std::set<Position>& visitedSpots)
{
    direction = calculateNewDirection(move[0], direction);

    int steps{};
    std::from_chars(move.data()+1, move.data()+move.size(), steps);

    const std::array<Position, 4> deltas {{{0,1},{1,0},{0,-1},{-1,0}}};
    const auto [dx, dy] = deltas[static_cast<int>(direction)];

    for (int i {1}; i <= steps; i++)
    {
        const auto newSpot = std::make_pair(currPos.first + dx*i, currPos.second + dy*i);
        if (visitedSpots.contains(newSpot))
            return {newSpot};
        visitedSpots.insert(newSpot);
    }

    currPos.first  += dx * steps;
    currPos.second += dy * steps;


    return {};
}


Position findFinalDestination(const std::vector<std::string>& moves)
{
    Position position {0, 0};
    Direction dir = Direction::NORTH;

    for (const auto& move : moves)
    {
        moveToNextSpot(position, dir, move);
    }

    return position;
}

Position findFirstDuplicate(const std::vector<std::string>& moves)
{
    Position position {0, 0};
    Direction dir = Direction::NORTH;

    std::set<std::pair<int,int>> visitedSpots{position};

    for (const auto& move: moves)
    {
        const auto intersection = moveToNextSpotIncrementally(position, dir, move, visitedSpots);
        if (intersection)
            return intersection.value();
    }

    assert(false); // shouldn't get here
    return {};
}


int main()
{
    const auto moves = getMoves("./2016/1.txt");
    const auto position = findFinalDestination(moves);
    const auto part1Ans = std::abs(position.first) + std::abs(position.second);

    assert(part1Ans == 241);

    const auto dupePosition = findFirstDuplicate(moves);
    const auto part2Ans = std::abs(dupePosition.first) + std::abs(dupePosition.second);

    assert(part2Ans == 116);

    std::cout << part1Ans << " " << part2Ans << "\n";


    return 0;
}
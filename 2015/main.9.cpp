#include <cassert>
#include "string_util.h"
#include <fstream>
#include <print>
#include <set>
#include <unordered_map>

using GraphMap = std::unordered_map<std::string, std::unordered_map<std::string, int32_t>>;

int32_t traverse(
    const GraphMap& graph,
    std::set<std::string>& visited,
    const std::string& currentPos,
    const int32_t currentDistance,
    const bool isFindingSmallest) {

    if (visited.size() == graph.size()) // visited everywhere
        return currentDistance;

    visited.insert(currentPos);

    const auto& destinations = graph.at(currentPos);

    int32_t currentRange = isFindingSmallest ?  std::numeric_limits<int32_t>::max() : std::numeric_limits<int32_t>::min();

    for (const auto& next: destinations) {
        if (visited.contains(next.first) == false) {
            visited.insert(next.first);

            if (isFindingSmallest)
                currentRange = std::min(currentRange, traverse(graph, visited, next.first, next.second + currentDistance, isFindingSmallest));
            else
                currentRange = std::max(currentRange, traverse(graph, visited, next.first, next.second + currentDistance, isFindingSmallest));

            visited.erase(next.first);
        }
    }

    return currentRange;
}

int main(int argc, const char *argv[]) {
    std::ifstream file{"./2015/9.txt"};

    GraphMap graph{};

    std::string line;
    while (std::getline(file, line)) {
        const auto splitLines = Shared::SplitLine(line, ' ');

        const auto& src = splitLines.at(0);
        const auto& dest = splitLines.at(2);
        const auto distance = std::stoi(splitLines.at(4));

        graph[src][dest] = distance;
        graph[dest][src] = distance;
    }

    // attempt every path to find smallest
    int smallest {std::numeric_limits<int32_t>::max()};

    for (const auto& [key, _] : graph) {
        std::set<std::string> visited {};
        smallest = std::min(smallest, traverse(graph, visited, key, 0, true));
    }

    assert(smallest == 207);

    int32_t largest {0};
    for (const auto& [key, _] : graph) {
        std::set<std::string> visited {};
        largest = std::max(largest, traverse(graph, visited, key, 0, false));
    }

    assert(largest == 804);

    std::println("{0} {1}", smallest, largest);
}

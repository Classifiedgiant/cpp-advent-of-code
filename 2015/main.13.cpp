#include <cassert>
#include <fstream>
#include <string>
#include <print>
#include <unordered_map>
#include <set>
#include <limits>

#include "string_util.h"

using SeatingMap = std::unordered_map<std::string, std::unordered_map<std::string, int32_t>>;

void AttemptBestSeating(
    const SeatingMap& seatingMap,
    std::vector<std::string>& seatedIndividuals,
    int32_t& currentHappiness,
    int32_t& maxHappiness) {
    // All the individuals have been seated
    if (seatedIndividuals.size() == seatingMap.size()) {
        maxHappiness = std::max(currentHappiness
        + seatingMap.at(seatedIndividuals.front()).at(seatedIndividuals.back())
        + seatingMap.at(seatedIndividuals.back()).at(seatedIndividuals.front()),
        maxHappiness);
        return;
    }

    for (const auto& [key, val] : seatingMap) {
        if (std::find(seatedIndividuals.begin(), seatedIndividuals.end(), key) == seatedIndividuals.end()) {
            const auto diffHappiness = seatingMap.at(seatedIndividuals.back()).at(key) + seatingMap.at(key).at(seatedIndividuals.back());
            currentHappiness += diffHappiness;
            seatedIndividuals.push_back(key);
            AttemptBestSeating(seatingMap, seatedIndividuals, currentHappiness, maxHappiness);
            seatedIndividuals.pop_back();
            currentHappiness -= diffHappiness;
        }
    }
}

int main(int argc, const char *argv[]) {
    std::ifstream fileStream{"./2015/13.txt"};

    // fill the map
    SeatingMap seatingMap{};
    std::string line{};
    while (std::getline(fileStream, line)) {
        const auto splitLine = Shared::SplitLine(line, ' ');
        auto lastVal = splitLine[splitLine.size() - 1];
        lastVal.erase(lastVal.size()-1);
        auto happiness = std::stoi(splitLine[3]);
        happiness = splitLine[2] == "gain" ? happiness : (happiness * -1);
        seatingMap[splitLine[0]][lastVal] = happiness;
    }

    int32_t part1Ans{std::numeric_limits<int32_t>::min()};
    for (const auto& [key, val]: seatingMap) {

        std::vector seatedIndividuals{key};
        int32_t localHappiness{0};
        AttemptBestSeating(seatingMap, seatedIndividuals, localHappiness, part1Ans);
    }

    assert(part1Ans == 733);

    // add us to the seatingMap
    std::vector<std::string> names;
    std::transform(seatingMap.begin(), seatingMap.end(), std::back_inserter(names), [](const auto& pair) { return pair.first; });

    std::for_each(seatingMap.begin(), seatingMap.end(), [](auto& elem) {elem.second["us"] = 0; });

    seatingMap.insert({"us", {}});
    for (const auto& name : names)
        seatingMap["us"][name] = 0;

    // loop through with us in the list
    int32_t part2Ans{std::numeric_limits<int32_t>::min()};
    for (const auto& [key, val]: seatingMap) {
        std::vector seatedIndividuals{key};
        int32_t localHappiness{0};
        AttemptBestSeating(seatingMap, seatedIndividuals, localHappiness, part2Ans);
    }

    assert(part2Ans == 725);
    std::println("{0}, {1}", part1Ans, part2Ans);
}

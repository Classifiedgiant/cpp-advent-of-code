#include <cassert>
#include <cstdint>
#include <fstream>
#include <iosfwd>
#include <optional>
#include <print>
#include <vector>

#include "string_util.h"

class SueInfo {
public:
    std::optional<int32_t> children;
    std::optional<int32_t> cats;
    std::optional<int32_t> samoyeds;
    std::optional<int32_t> pomeranians;
    std::optional<int32_t> akitas;
    std::optional<int32_t> vizslas;
    std::optional<int32_t> goldfish;
    std::optional<int32_t> trees;
    std::optional<int32_t> cars;
    std::optional<int32_t> perfumes;

    auto operator<=>(const SueInfo &) const = default;
};

using SueVector = std::vector<SueInfo>;

SueInfo createSueFromLine(const std::string& line) {

    auto splitLine = Shared::SplitLine(line, ' ');

    SueInfo sueInfo;
    // Skip "Sue 1:" start at 1
    for (int i = 2; i < splitLine.size(); i+=2) {
        if (splitLine[i] == "children:") {
            sueInfo.children = std::stoi(splitLine.at(i+1));
        }
        else if (splitLine[i] == "cats:") {
            sueInfo.cats = std::stoi(splitLine[i+1]);
        }
        else if (splitLine[i] == "samoyeds:") {
            sueInfo.samoyeds = std::stoi(splitLine[i+1]);
        }
        else if (splitLine[i] == "pomeranians:") {
            sueInfo.pomeranians = std::stoi(splitLine[i+1]);
        }
        else if (splitLine[i] == "akitas:") {
            sueInfo.akitas = std::stoi(splitLine[i+1]);
        }
        else if (splitLine[i] == "vizslas:") {
            sueInfo.vizslas = std::stoi(splitLine[i+1]);
        }
        else if (splitLine[i] == "goldfish:") {
            sueInfo.goldfish = std::stoi(splitLine[i+1]);
        }
        else if (splitLine[i] == "trees:") {
            sueInfo.trees = std::stoi(splitLine[i+1]);
        }
        else if (splitLine[i] == "cars:") {
            sueInfo.cars = std::stoi(splitLine[i+1]);
        }
        else if (splitLine[i] == "perfumes:") {
            sueInfo.perfumes = std::stoi(splitLine[i+1]);
        }
    }

    return sueInfo;
}

SueVector readAllSueNotes(std::ifstream& file) {
    if (file.is_open() == false)
        throw std::runtime_error("File read failure");

    SueVector sues;
    sues.reserve(500);
    std::string line;
    while (getline(file, line)) {
        sues.push_back(createSueFromLine(line));
    }

    return sues;
}


int main (int argc, const char* argv[]) {

    std::ifstream file{"./2015/16.txt"};
    const auto sues = readAllSueNotes(file);


    SueInfo expectedSue {
        .children = 3,
        .cats = 7,
        .samoyeds = 2,
        .pomeranians = 3,
        .akitas =  0,
        .vizslas = 0,
        .goldfish =  5,
        .trees = 3,
        .cars = 2,
        .perfumes = 1
    };

    const auto res = std::find_if(sues.begin(), sues.end(), [&expectedSue](const auto& elem) {
        if (elem.children and elem.children != expectedSue.children) return false;
        if (elem.cats and elem.cats != expectedSue.cats) return false;
        if (elem.samoyeds and elem.samoyeds != expectedSue.samoyeds) return false;
        if (elem.pomeranians and elem.pomeranians != expectedSue.pomeranians) return false;
        if (elem.akitas and elem.akitas != expectedSue.akitas) return false;
        if (elem.vizslas and elem.vizslas != expectedSue.vizslas) return false;
        if (elem.goldfish and elem.goldfish != expectedSue.goldfish) return false;
        if (elem.trees and elem.trees != expectedSue.trees) return false;
        if (elem.cars and elem.cars != expectedSue.cars) return false;
        if (elem.perfumes and elem.perfumes != expectedSue.perfumes) return false;

        return true;
    });
    const auto part1Ans {std::distance(sues.begin(), res)+1};
    assert(part1Ans == 213);

    const auto newRes = std::find_if(sues.begin(), sues.end(), [&expectedSue](const auto& elem) {
        if (elem.children and elem.children != expectedSue.children) return false;
        if (elem.cats and elem.cats <= expectedSue.cats) return false;
        if (elem.samoyeds and elem.samoyeds != expectedSue.samoyeds) return false;
        if (elem.pomeranians and elem.pomeranians >= expectedSue.pomeranians) return false;
        if (elem.akitas and elem.akitas != expectedSue.akitas) return false;
        if (elem.vizslas and elem.vizslas != expectedSue.vizslas) return false;
        if (elem.goldfish and elem.goldfish >= expectedSue.goldfish) return false;
        if (elem.trees and elem.trees <= expectedSue.trees) return false;
        if (elem.cars and elem.cars != expectedSue.cars) return false;
        if (elem.perfumes and elem.perfumes != expectedSue.perfumes) return false;

        return true;
    });

    const auto part2Ans {std::distance(sues.begin(), newRes)+1};
    assert(part2Ans == 323);

    std::println("{0}, {1}", part1Ans, part2Ans);
}

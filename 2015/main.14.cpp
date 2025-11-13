#include <cassert>
#include <algorithm>
#include <fstream>
#include <print>
#include <string>
#include <unordered_map>
#include "string_util.h"

struct ReindeerInfo {
    int32_t distance;
    int32_t points;
    const int8_t flyingSpeed;
    const int8_t flyingTime;
    const int8_t restTime;
    int8_t elapsedStateTime;
    bool isFlying;
};

int main(int argc, const char *argv[]) {
    auto file = std::fstream{"2015/14.txt"};

    std::pmr::unordered_map<std::string, ReindeerInfo> reindeerInfo{};

    std::string line;
    while (getline(file, line)) {
        const auto splitLine = Shared::SplitLine(line, ' ');
       reindeerInfo.insert({splitLine[0], ReindeerInfo { 0,
           0,
           static_cast<int8_t>(stoi(splitLine[3])),
           static_cast<int8_t>(stoi(splitLine[6])),
           static_cast<int8_t>(stoi(splitLine[13])),
       0,
       true}});
    }

    int32_t elapsedTime{0};
    constexpr int32_t totalSeconds{2503};
    while (elapsedTime <= totalSeconds) {
        for (auto& [k, v]: reindeerInfo) {
            auto stateThreshold = v.restTime;
            if (v.isFlying) {
                v.distance += v.flyingSpeed;
                stateThreshold = v.flyingTime;
            }

            v.elapsedStateTime++;

            if (v.elapsedStateTime == stateThreshold) {
                v.elapsedStateTime = 0;
                v.isFlying = not v.isFlying;
            }
        }

        elapsedTime++;
    }

    auto maxDistance = std::max_element(reindeerInfo.begin(), reindeerInfo.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs.second.distance < rhs.second.distance;
        });

    const auto part1Ans{maxDistance->second.distance};
    assert(part1Ans == 2640);

    std::for_each(reindeerInfo.begin(), reindeerInfo.end(), [](auto& elem) {
        elem.second.distance = 0;
        elem.second.isFlying = true;
        elem.second.elapsedStateTime = 0;
    });

    elapsedTime = 0;
    while (elapsedTime <= totalSeconds) {
        int32_t maxDistance {0};
        for (auto& [k, v]: reindeerInfo) {
            auto stateThreshold = v.restTime;
            if (v.isFlying) {
                v.distance += v.flyingSpeed;
                stateThreshold = v.flyingTime;
            }

            v.elapsedStateTime++;

            if (v.elapsedStateTime == stateThreshold) {
                v.elapsedStateTime = 0;
                v.isFlying = not v.isFlying;
            }

            maxDistance = std::max(maxDistance, v.distance);
        }

        elapsedTime++;

        std::for_each(reindeerInfo.begin(), reindeerInfo.end(), [&](auto& elem) {
           if (elem.second.distance == maxDistance)
               elem.second.points++;
        });
    }

    const auto maxPoints = std::max_element(reindeerInfo.begin(), reindeerInfo.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs.second.points < rhs.second.points;
        });
    const auto part2Ans {maxPoints->second.points};
    assert(part2Ans == 1102);

    std::println("{0}, {1}", part1Ans, part2Ans);

}

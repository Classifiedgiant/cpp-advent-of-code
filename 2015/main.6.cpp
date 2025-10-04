#include <cassert>
#include <fstream>
#include <ranges>
#include <vector>
#include <print>

std::vector<std::string> SplitLine(const std::string& line, char delimiter) {
    return line
        | std::views::split(delimiter)
    | std::views::transform([](auto &&range) { return std::string(range.begin(), range.end()); })
    | std::ranges::to<std::vector>();
}

void SwitchLights (
    const std::pair<int, int> start,
    const std::pair<int, int> end,
    std::vector<std::vector<bool>>& lights,
    int& lightCount,
    const std::optional<bool> switchOn) {
    // null toggle
    // true on
    // false off

    for (int col{start.first}; col <= start.second; col++) {
        for (int row{end.first}; row <= end.second; row++) {
            if (switchOn.has_value()) {
                // on or off

                if (switchOn.value() != lights[col][row]) {
                    lightCount = switchOn.value() ? lightCount+1 : lightCount-1;
                }
                lights[col][row] = switchOn.value();
            }
            else {
                // toggle
                lightCount = lights[col][row] ? lightCount-1 : lightCount+1;
                lights[col][row] = !lights[col][row];
            }
        }
    }
}

void SwitchBrightness (
    const std::pair<int, int> start,
    const std::pair<int, int> end,
    std::vector<std::vector<int>>& lights,
    int& brightnessCount,
    const std::optional<bool> switchOn) {
    // std::optional<bool>
    // null toggle
    // true on
    // false off

    for (int col{start.first}; col <= start.second; col++) {
        for (int row{end.first}; row <= end.second; row++) {
            if (switchOn.has_value()) {
                // on or off

                if (switchOn.value()) {
                    brightnessCount++;
                }
                else {
                    if (lights[col][row] > 0)
                        brightnessCount--;
                }
                lights[col][row] = switchOn.value() ? lights[col][row]+1 : std::max(lights[col][row]-1, 0);
            }
            else {
                // toggle
                brightnessCount += 2;
                lights[col][row] += 2;
            }
        }
    }
}

int calculateLightCount(std::string line, std::vector<std::vector<bool>>& lights, int& lightCount) {
    const auto lineSplit = SplitLine(line, ' ');

    if (lineSplit.size() == 4) {
        // toggle
        const auto start = SplitLine(lineSplit[1], ',');
        const auto end = SplitLine(lineSplit[3], ',');

        int xStart{std::stoi(start[0])};
        int yStart{std::stoi(start[1])};

        int xEnd{std::stoi(end[0])};
        int yEnd{std::stoi(end[1])};

        SwitchLights({xStart, xEnd}, {yStart, yEnd}, lights, lightCount, std::nullopt);
    }
    else {
        // turn on/off
        const auto start = SplitLine(lineSplit[2], ',');
        const auto end = SplitLine(lineSplit[4], ',');

        int xStart{std::stoi(start[0])};
        int yStart{std::stoi(start[1])};

        int xEnd{std::stoi(end[0])};
        int yEnd{std::stoi(end[1])};

        const bool isSwitchOn{lineSplit[1] == "on"};

        SwitchLights({xStart, xEnd}, {yStart, yEnd}, lights, lightCount, isSwitchOn);
    }

    return lightCount;
}

int calculateLightBrightness(std::string line, std::vector<std::vector<int>>& lightBrightness, int& lightCount) {
    const auto lineSplit = SplitLine(line, ' ');

    if (lineSplit.size() == 4) {
        // toggle
        const auto start = SplitLine(lineSplit[1], ',');
        const auto end = SplitLine(lineSplit[3], ',');

        int xStart{std::stoi(start[0])};
        int yStart{std::stoi(start[1])};

        int xEnd{std::stoi(end[0])};
        int yEnd{std::stoi(end[1])};

        SwitchBrightness({xStart, xEnd}, {yStart, yEnd}, lightBrightness, lightCount, std::nullopt);
    }
    else {
        // turn on/off
        const auto start = SplitLine(lineSplit[2], ',');
        const auto end = SplitLine(lineSplit[4], ',');

        int xStart{std::stoi(start[0])};
        int yStart{std::stoi(start[1])};

        int xEnd{std::stoi(end[0])};
        int yEnd{std::stoi(end[1])};

        const bool isSwitchOn{lineSplit[1] == "on"};

        SwitchBrightness({xStart, xEnd}, {yStart, yEnd}, lightBrightness, lightCount, isSwitchOn);
    }

    return lightCount;
}

int main(int argc, const char *argv[]) {
    // assert(calculateLight("turn on 0,0 through 999,999", lights, lightCount) == 1000000);
    // assert(calculateLight("turn off 0,0 through 999,999", lights, lightCount) == 0);
    // assert(calculateLight("toggle 0,0 through 2,2", lights, lightCount) == 9);

    std::ifstream file{"./2015/6.txt"};
    int lightCount{0};
    std::vector lights(1000, std::vector(1000, false));

    // Day 1
    std::string line;
    while (std::getline(file, line)) {
        calculateLightCount(line, lights, lightCount);
    }

    // reset file
    file.clear();
    file.seekg(0, std::ios::beg);
    int brightness{0};
    std::vector lightBrightness(1000, std::vector(1000, 0));
    // assert(calculateLightBrightness("turn on 0,0 through 999,999", lightBrightness, brightness) == 1000000);
    // assert(calculateLightBrightness("turn off 0,0 through 999,999", lightBrightness, brightness) == 0);
    // assert(calculateLightBrightness("turn off 0,0 through 999,999", lightBrightness, brightness) == 0);
    // assert(calculateLightBrightness("toggle 0,0 through 999,999", lightBrightness, brightness) == 2000000);

    while (std::getline(file, line)) {
        calculateLightBrightness(line, lightBrightness, brightness);
    }


    std::println("{0} {1}", lightCount, brightness);
}

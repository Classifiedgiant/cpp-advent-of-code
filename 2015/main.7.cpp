#include <cassert>
#include <fstream>
#include <ranges>
#include <vector>
#include <print>
#include <unordered_map>

std::vector<std::string> SplitLine(std::string_view line, char delimiter) {
    return line
        | std::views::split(delimiter)
    | std::views::transform([](auto &&range) { return std::string(range.begin(), range.end()); })
    | std::ranges::to<std::vector>();
}

bool isStringAllDigits(const std::string_view string) {
    return std::all_of(string.begin(), string.end(), [](const auto elem){ return std::isdigit(elem);});
}

enum class Action {
    SET,
    AND,
    OR,
    LSHIFT,
    RSHIFT,
    NOT,
};

struct SignalNode {
    std::vector<std::string> inputs;
    Action action;
    std::optional<u_int16_t> value;
};

using SignalMap = std::unordered_map<std::string, SignalNode>;

Action FindAction(const std::string& string) {
    const std::unordered_map<std::string, Action> stringMapper {
        {"AND", Action::AND},
        {"OR", Action::OR},
        {"LSHIFT", Action::LSHIFT},
        {"RSHIFT", Action::RSHIFT}
    };

    if (stringMapper.contains(string))
        return stringMapper.at(string);

    assert(false);
}

void SetWireSignal(const std::string_view line, SignalMap& signals) {
    const auto splitLine = SplitLine(line, ' ');
    const auto& nodeName = splitLine[splitLine.size()-1];
    // assert(signals.contains(nodeName) == false);
    if (signals.contains(nodeName))
        return;

    switch (splitLine.size()) {
        case 3: {
            // assignment
            const auto& input = splitLine.at(0);
            if (isStringAllDigits(input)) {
               // 123 -> y
               signals.insert_or_assign(nodeName, SignalNode{{}, Action::SET, std::stoi(input)});
            } else {
               // x -> y
               signals.insert_or_assign(nodeName, SignalNode{{input}, Action::SET, {}});
            }
            break;
        }
        case 4: {
            // not
            const auto& input = splitLine.at(1);
            if (isStringAllDigits(input)) {
                // NOT 123123 -> x
                signals.insert_or_assign(nodeName, SignalNode{{}, Action::NOT, ~std::stoi(input)});
            } else {
                // NOT y -> x
                signals.insert_or_assign(nodeName, SignalNode{{input}, Action::NOT, {}});
            }
            break;
        }
        case 5: {
            // Combination
            // x and y ->
            const auto& lhs = splitLine.at(0);
            const auto& rhs = splitLine.at(2);
            const auto& action = splitLine.at(1);
            signals.insert_or_assign(nodeName, SignalNode{{lhs, rhs}, FindAction(action), {}});
            break;
        }
        default:
            // we have received invalid input
            assert(false);
    }
}

std::optional<u_int16_t> getValue(const SignalMap& map, const std::string& str) {
    if (map.contains(str) && map.at(str).value) {
        return map.at(str).value.value();
    }

    if (isStringAllDigits(str)) {
        return static_cast<u_int16_t>(std::stoi(str));
    }
    return {};
}

bool calculateValue(const SignalMap& signals, SignalNode& node) {
    const bool allInputsHaveValues = std::all_of(node.inputs.begin(), node.inputs.end(), [&signals](const auto& elem) {
        if (signals.contains(elem))
            return signals.at(elem).value.has_value();

        return isStringAllDigits(elem);
    });

    if (!allInputsHaveValues)
        return false;

    bool isCalculated {false};

    switch (node.action) {
        case Action::AND: {
            const auto lhs = getValue(signals, node.inputs.at(0));
            const auto rhs = getValue(signals, node.inputs.at(1));
            if (lhs && rhs) {
                node.value = lhs.value() & rhs.value();
                isCalculated = true;
            }
            break;
        }
        case Action::OR: {
            const auto lhs = getValue(signals, node.inputs.at(0));
            const auto rhs = getValue(signals, node.inputs.at(1));
            if (lhs && rhs) {
                node.value = lhs.value() | rhs.value();
                isCalculated = true;
            }
            break;
        }
        case Action::LSHIFT: {
            const auto lhs = getValue(signals, node.inputs.at(0));
            const auto rhs = getValue(signals, node.inputs.at(1));
            if (lhs && rhs) {
                node.value = lhs.value() << rhs.value();
                isCalculated = true;
            }
            break;
        }
        case Action::RSHIFT: {
            const auto lhs = getValue(signals, node.inputs.at(0));
            const auto rhs = getValue(signals, node.inputs.at(1));
            if (lhs && rhs) {
                node.value = lhs.value() >> rhs.value();
                isCalculated =  true;
            }
            break;
        }
        case Action::NOT: {
            const auto lhs = getValue(signals, node.inputs.at(0));
            if (lhs) {
                node.value = ~lhs.value();
                isCalculated = true;
            }
            break;
        }
        case Action::SET: {
            const auto lhs = getValue(signals, node.inputs.at(0));
            if (lhs) {
                node.value = lhs.value();
                isCalculated = true;
            }
            break;
        }
    }
    return isCalculated;
}

void calculateSignals(SignalMap& signals) {
    while (signals.at("a").value.has_value() == false) {
        auto filterView = signals | std::views::filter([](const auto& signalNode) {
            return !signalNode.second.value.has_value();
        }) | std::ranges::to<std::vector>();

        for (auto& nodePair : filterView) {
            calculateValue(signals, signals.at(nodePair.first));
        }
    }
}

int main(int argc, const char *argv[]) {
    std::ifstream file{"./2015/7.txt"};

    SignalMap signalWires{};

    // Part 1
    std::string line;
    while (std::getline(file, line)) {
        SetWireSignal(line, signalWires);
    }

    calculateSignals(signalWires);


    const auto part1Answer{signalWires.at("a").value.value()};
    assert (part1Answer == 956);
    // Part 2
    signalWires.clear();

    // reset file
    file.clear();
    file.seekg(0, std::ios::beg);

    // set "b" to
    signalWires["b"] = SignalNode{{}, Action::SET, part1Answer};
    while (std::getline(file, line)) {
        SetWireSignal(line, signalWires);
    }

    calculateSignals(signalWires);
    const auto part2Answer{signalWires.at("a").value.value()};
    assert(part2Answer == 40149);

    std::println("{0}, {1}", part1Answer, part2Answer);
}

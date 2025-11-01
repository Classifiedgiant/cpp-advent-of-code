#include <cassert>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <print>

using json = nlohmann::json;

int32_t ReadJson(const json& data) {
    int32_t subSum{0};
    for (const auto& [key, val] : data.items()) {
        if (val.is_object()) {
            subSum += ReadJson(val);
        }

        if (val.is_array()) {
            int32_t arrVal{0};
            for (const auto& subVal : val) {
                arrVal += ReadJson(subVal);
            }
            subSum += arrVal;
        }

        if (val.is_number()) {
            subSum += val.get<int32_t>();
        }

        if (!data.is_array() && val.is_string() && val.get<std::string>() == "red")
            return 0;

    }

    return subSum;
}

int main(int argc, const char *argv[]) {
    std::ifstream fileStream{"./2015/12.txt"};

    int32_t sum{0};
    std::string line;
    if (std::getline(fileStream, line)) {
        for (int i{0}; i < line.size(); i++) {
            if (i < line.size() && isdigit(line[i])) {
                const bool is_negative = line[i-1] == '-';

                int32_t curr = i;
                while (curr < line.size() && isdigit(line[curr])) {
                    curr++;
                }

                const auto val = stoi(std::string(line, i, curr-i+1));
                sum += is_negative ? -1 * val : val;
                i = curr;
            }
        }
    }

    const auto part1Answer {sum};
    assert(part1Answer == 119433);
    fileStream.clear();
    fileStream.seekg(0, std::ios::beg);

    assert(ReadJson(json::parse(R"({"a": [1,2,3]})")) == 6);
    assert(ReadJson(json::parse(R"({"a": [1,"red",5]})")) == 6);
    assert(ReadJson(json::parse(R"({"a": "red", "b": [1,2,3], "c": 4})")) == 0);
    assert(ReadJson(json::parse(R"({"a": { "b": { "c": 4 }, "d": {"e": "red"}}})"))== 4);
    assert(ReadJson(json::parse(R"({"a": {"b" :[1,10]}, "c": [[10, 10, "red"], {"e": "red"}]})")) == 31);

    json data = json::parse(fileStream);

    const auto part2Answer = ReadJson(data);
    assert(part2Answer == 68466);
    std::println("{0} {1}", part1Answer, part2Answer);
}

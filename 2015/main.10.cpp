#include <cassert>
#include <cstdint>
#include <string>
#include <string_view>
#include <sstream>
#include <print>

std::string inputValue(std::string_view str) {
    std::stringstream output{};

    uint32_t i{0};
    uint32_t slow{0};

    while (i < str.size()) {
        while (i < str.size() && str[i] == str[slow]) {
            i++;
        }

        output << (i-slow) << str[slow];
        slow = i;
    }

    return output.str();
}

int main(int argc, const char *argv[]) {
    assert(inputValue("1111111") == "71");
    assert(inputValue("1") == "11");

    const std::string input {"3113322113" };

    std::string day1Answer{input};
    for (int i = 0; i < 40; i++) {
        day1Answer = inputValue(day1Answer);
    }

    std::string day2Answer{input};
    for (int i = 0; i < 50; i++) {
        day2Answer = inputValue(day2Answer);
    }

    assert(day1Answer.size() == 329356);
    assert(day2Answer.size() == 4666278);

    std::println("{0}, {1}", day1Answer.size(), day2Answer.size());

}

#include <cassert>
#include <cstdint>
#include <string>
#include <print>
#include <unordered_set>

bool hasThreeConsecutiveChars(std::string_view str) {
    for (int i = 2; i < str.size(); i++) {
        if (str[i-1] == str[i]-1 && str[i-2] == str[i-1]-1)
            return true;
    }

    return false;
}

bool hasIOLChars(std::string_view str) {
    std::unordered_set invalidChars = {'i', 'o', 'l'};

    return std::any_of(invalidChars.begin(), invalidChars.end(), [&str](const auto ch){ return str.contains(ch);});
}

bool hasTwoNonOverlappingPairs(std::string_view str) {
    int doubleCount{0};

    for (int i = 0; i < str.size(); i++) {
        if (i < str.size()-1 && str[i] == str[i+1]) {
            doubleCount++;
            i++;
            if (doubleCount > 1)
                return true;
        }
    }
    return false;
}

std::string nextPassword(const std::string_view old_password) {
    assert(old_password.size() == 8);
    std::string new_password{old_password};

    while (old_password== new_password
        || hasIOLChars(new_password)
        || !hasThreeConsecutiveChars(new_password)
        || !hasTwoNonOverlappingPairs(new_password)) {

        int32_t i = new_password.size() - 1;

        while (i >= 0 && new_password[i] == 'z') {
            new_password[i] = 'a';
            i--;
        }
        new_password[i]++;
    }

    return new_password;
}

int main(int argc, const char *argv[]) {
    std::string input = "hxbxwxba";

    std::string part1Answer = nextPassword(input);
    assert(part1Answer == "hxbxxyzz");

    std::string part2Answer = nextPassword(part1Answer);
    assert(part2Answer == "hxcaabcc");

    std::println("{0}, {1}", part1Answer, part2Answer);
}

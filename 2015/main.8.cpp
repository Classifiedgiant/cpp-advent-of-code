#include <cassert>
#include <fstream>
#include <print>
#include <iostream>

int calculateChars(const std::string& str) {
    int count{0};

    int i{0};
    while (i < str.size()) {
        const auto ch = str[i];
        if (ch == '\\' && i+1 < str.size() && str[i+1] == '\\') {
            i+=2;
        } else if (ch == '\\' && i+1 < str.size() && str[i+1] == '\"') {
            i+=2;
        } else if (ch == '\\' && i+1 < str.size() && str[i+1] == 'x') {
            i+=4;
        } else {
            i++;
        }

        count++;

    }

    return count;
}

int newEncoding(const std::string& str) {
    int count{0};

    for (const auto ch: str) {
        if (ch == '\\')
            count += 2;
        else if (ch == '\"')
            count += 2;
        else
            count++;
    }

    return count + 2;
}

int main(int argc, const char *argv[]) {
    std::ifstream file{"./2015/8.txt"};

    assert(calculateChars("") == 0);
    assert(calculateChars("abc") == 3);
    assert(calculateChars("aaa\"aaa") == 7);
    assert(calculateChars("\x27") == 1);

    u_int32_t literalChars {0};
    u_int32_t memChars {0};
    std::string line;
    while (std::getline(file, line)) {
        literalChars += line.size();
        memChars += calculateChars(line)-2;
    }

    const auto part1Answer{literalChars - memChars};
    assert(part1Answer == 1371);

    file.clear();
    file.seekg(0, std::ios::beg);

    literalChars = 0;
    uint32_t newEncodingCount = 0;

    while (std::getline(file, line)) {
        literalChars += line.size();
        newEncodingCount += newEncoding(line);
    }

    const auto part2Answer {newEncodingCount - literalChars};
    assert(part2Answer == 2117);
    std::println("{0}, {1}", part1Answer, part2Answer);

}

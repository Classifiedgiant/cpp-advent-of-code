#ifndef ADVENT_OF_CODE_SHARED_STRING_UTIL
#define ADVENT_OF_CODE_SHARED_STRING_UTIL

#include <string>
#include <ranges>
#include <vector>

namespace Shared {
std::vector<std::string> SplitLine(const std::string& line, char delimiter) {
    return line
        | std::views::split(delimiter)
    | std::views::transform([](auto &&range) { return std::string(range.begin(), range.end()); })
    | std::ranges::to<std::vector>();
}
} // Shared

#endif //ADVENT_OF_CODE_SHARED_STRING_UTIL

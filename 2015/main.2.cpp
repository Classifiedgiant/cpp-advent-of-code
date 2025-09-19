#include <charconv>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

std::vector<int> getLengths(std::string line, char delimiter) {
  auto lineNumbers = line | std::views::split(delimiter) |
                     std::views::transform([](auto &&range) {
                       std::string_view sv(range.begin(), range.end());
                       int value{0};
                       std::from_chars(sv.begin(), sv.end(), value);
                       return value;
                     });
  return lineNumbers | std::ranges::to<std::vector>();
}

int main(int argc, const char *argv[]) {

  std::print("Lockie\n");

  // run from the repo root
  std::ifstream file("./build/2015/2.txt");
  std::print("{0}", file.is_open());

  std::string line;

  int total{};

  while (std::getline(file, line)) {

    const auto dimensions = getLengths(line, 'x');

    auto w = dimensions[0];
    auto l = dimensions[1];
    auto h = dimensions[2];

    const auto wh = w * h;
    const auto hl = l * h;
    const auto lw = l * w;
    const std::vector<int> areas = {wh, hl, lw};

    const auto addition = *std::min_element(areas.begin(), areas.end());

    total += (2 * wh) + (2 * hl) + (2 * lw) + addition;
  }

  std::println("{0}", total);
}

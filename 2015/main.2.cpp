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
  // run from the repo root
  std::ifstream file("./build/2015/2.txt");
  std::string line;

  int wrappingPaper{};
  int ribbon{};

  while (std::getline(file, line)) {

    const auto dimensions = getLengths(line, 'x');

    auto w = dimensions[0];
    auto l = dimensions[1];
    auto h = dimensions[2];
    std::vector<int> dimes{w, l, h};
    std::sort(dimes.begin(), dimes.end());

    const auto wh = w * h;
    const auto hl = l * h;
    const auto lw = l * w;
    std::vector<int> areas = {wh, hl, lw};
    std::sort(areas.begin(), areas.end());

    wrappingPaper += (2 * wh) + (2 * hl) + (2 * lw) + areas.at(0);

    ribbon +=
        (2 * dimes[0]) + (2 * dimes[1]) + (dimes[0] * dimes[1] * dimes[2]);
  }

  std::println("{0}, {1}", wrappingPaper, ribbon);
}

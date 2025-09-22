#include <algorithm>
#include <cassert>
#include <fstream>
#include <print>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool isGood(const std::string_view &line) {
  const std::unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};

  const std::vector<std::string> disallowedValues{"ab", "cd", "pq", "xy"};

  if (std::any_of(disallowedValues.begin(), disallowedValues.end(),
                  [&line](const auto &elem) { return line.contains(elem); }))
    return false;

  int vowelCounter{0};
  bool consecutiveChar{false};
  for (int i{0}; i < line.size(); i++) {
    if (vowels.contains(line[i]))
      vowelCounter++;

    if (i > 0 && line[i] == line[i - 1])
      consecutiveChar = true;
  }

  return vowelCounter >= 3 && consecutiveChar;
}

bool isGoodPart2(const std::string_view line) {
  std::unordered_map<char, std::vector<int>> charMarkers{};
  charMarkers[line[0]];

  bool palindromeChars{false};
  bool dualGroup{false};
  for (int i{1}; i < line.size(); i++) {
    if (i - 1 >= 0 && i + 1 < line.size() && line[i - 1] == line[i + 1])
      palindromeChars = true;

    const auto ch = line[i];
    if (charMarkers.contains(ch)) {
      for (const auto prevChar : charMarkers[ch]) {
        if (prevChar - 1 >= 0 && i - 1 > prevChar &&
            line[prevChar - 1] == line[i - 1]) {
          dualGroup = true;
          break;
        }
      }
    }

    charMarkers[ch].push_back(i);

    if (palindromeChars && dualGroup)
      return true;
  }

  return false;
}

int main(int argc, const char *argv[]) {
  // Examples
  // part 1
  assert(isGood("ugknbfddgicrmopn"));
  assert(isGood("aaa"));
  assert(!isGood("jchzalrnumimnmhp"));
  assert(!isGood("haegwjzuvuyypxyu"));
  assert(!isGood("dvszwmarrgswjxmb"));

  // part 2
  assert(isGoodPart2("qjhvhtzxqqjkmpb"));
  assert(isGoodPart2("xxyxx"));
  assert(!isGoodPart2("uurcxstgmygtbstg"));
  assert(!isGoodPart2("ieodomkazucvgmuy"));

  std::ifstream file{"./2015/5.txt"};
  int counter{0};

  std::string line;
  while (std::getline(file, line)) {
    if (isGood(line))
      counter++;
  }

  file.clear();
  file.seekg(0, std::ios::beg);

  int counterPart2{0};
  while (std::getline(file, line)) {
    if (isGoodPart2(line))
      counterPart2++;
  }

  std::println("{0}, {1}", counter, counterPart2);
}

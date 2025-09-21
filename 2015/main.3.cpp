#include <cstddef>
#include <fstream>
#include <ios>
#include <print>
#include <set>

std::size_t visitHousesWithOneSanta(std::ifstream &file) {

  std::pair<int, int> currPosition{0, 0};
  std::set<std::pair<int, int>> prevPositions{currPosition};

  char buf;
  while (file.get(buf)) {
    switch (buf) {
    case 'v':
      currPosition.second--;
      break;
    case '<':
      currPosition.first--;
      break;
    case '>':
      currPosition.first++;
      break;
    case '^':
      currPosition.second++;
      break;
    default:
      std::print("Could not find: {0}", buf);
    }

    prevPositions.insert(currPosition);
  }
  return prevPositions.size();
}

std::size_t visitHousesWithTwoSantas(std::ifstream &file) {

  std::pair<int, int> cp1{0, 0};
  std::pair<int, int> cp2{0, 0};
  auto firstSantaMove = true;

  std::set<std::pair<int, int>> prevPositions{cp1};

  char buf;
  while (file.get(buf)) {
    auto &currPosition = firstSantaMove ? cp1 : cp2;
    switch (buf) {
    case 'v':
      currPosition.second--;
      break;
    case '<':
      currPosition.first--;
      break;
    case '>':
      currPosition.first++;
      break;
    case '^':
      currPosition.second++;
      break;
    default:
      std::print("Could not find: {0}", buf);
    }

    prevPositions.insert(currPosition);
    firstSantaMove = !firstSantaMove;
  }
  return prevPositions.size();
}

int main(int argc, const char *argv[]) {
  // run from the repo root
  std::ifstream file("./build/2015/3.txt");

  const auto houseVisited = visitHousesWithOneSanta(file);

  file.clear();
  file.seekg(0, std::ios::beg);

  const auto houseVisitedTwoSantas = visitHousesWithTwoSantas(file);

  std::println("{0}, {1}", houseVisited, houseVisitedTwoSantas);
}

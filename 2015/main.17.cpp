#include <cassert>
#include <map>
#include <vector>
#include <print>

void traverseContainers(const std::vector<int> containers, int i, int currentVolume, int& count) {
   if (currentVolume == 150) {
      count++;
      return;
   }

   if (currentVolume > 150)
      return;

   for (; i < containers.size(); i++) {
      traverseContainers(containers, i+1, currentVolume+containers[i], count);
   }
}

void part2Traversal(std::vector<int> containers, int i, int currentVolume, int currContainerCount, std::map<int, int>& containerCounts) {
   if (currentVolume == 150) {
      containerCounts[currContainerCount]++;
      return;
   }

   if (currentVolume > 150)
      return;

   for (; i < containers.size(); i++) {
      part2Traversal(containers, i+1, currentVolume+containers[i], currContainerCount+1, containerCounts);
   }
}

int main(int argc, const char* argv[]) {
   std::vector containers{
      43,
      3,
      4,
      10,
      21,
      44,
      4,
      6,
      47,
      41,
      34,
      17,
      17,
      44,
      36,
      31,
      46,
      9,
      27,
      38};

   int part1Ans{0};
   traverseContainers(containers, 0, 0, part1Ans);
   assert(part1Ans == 1638);

   std::map<int, int> containerCounts{};
   part2Traversal(containers, 0, 0, 0, containerCounts);
   int part2Ans{containerCounts.begin()->second};
   assert(part2Ans == 17);

   std::println("{0}, {1}", part1Ans, part2Ans);

   return 0;
}

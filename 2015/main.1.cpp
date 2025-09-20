#include <assert.h>
#include <fstream>
#include <string>
#include <string_view>
#include <version>

#if __cpp_lib_print >= 202207L
#include <print>
#else
#error "Unable to support std::print"
#endif

int calculateFloor(std::string_view str) {
  int floor{0};

  for (const auto ch : str) {

    if (ch == '(')
      floor++;
    else
      floor--;
  }

  return floor;
}

int calculateFirstBasement(std::string_view str) {
  int curr_floor{0};
  int i = 0;

  for (const auto ch : str) {
    if (ch == '(')
      curr_floor++;
    else {
      curr_floor--;

      if (curr_floor == -1)
        return i + 1;
    }

    i++;
  }

  // should not get here (Santa must get to the basement)
  assert(false);

  return -1;
}

int main(int argc, const char *argv[]) {

  // Day 1 part 1 answer
  // The examples from day 1 part 1
  assert(calculateFloor("(())") == 0);
  assert(calculateFloor("()()") == 0);
  assert(calculateFloor("(((") == 3);
  assert(calculateFloor("(()(()(") == 3);
  assert(calculateFloor("())") == -1);
  assert(calculateFloor("))(") == -1);
  assert(calculateFloor(")))") == -3);
  assert(calculateFloor(")())())") == -3);

  std::ifstream file("./build/2015/1.txt");
  const auto content = std::string(std::istreambuf_iterator<char>(file),
                                   std::istreambuf_iterator<char>());

  const auto finalFloor = calculateFloor(content);
  const auto firstBasement = calculateFirstBasement(content);

  // Generate the answer using the input argument
  std::println("{0}, {1}", finalFloor, firstBasement);

  return 0;
}

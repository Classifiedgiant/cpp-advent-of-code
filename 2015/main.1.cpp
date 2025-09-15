#include <assert.h>
#include <version>

#if defined(__cpp_lib_print)
#include <print>
#else
#error "Unable to support std::print"
#endif

int calculateFloor(const char *str) {
  int floor{0};

  while (*str != '\0') {
    if (*str == '(')
      floor++;
    else
      floor--;

    str++;
  }

  return floor;
}

int calculateFirstBasement(const char *str) {
  int curr_floor{0};
  int i = 0;

  while (*str != '\0') {
    if (*str == '(')
      curr_floor++;
    else
      curr_floor--;

    if (curr_floor == -1)
      return i + 1;

    str++;
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

  // Generate the answer using the input argument
  std::print("{0}\n", calculateFloor(argv[1]));
  // generates 232

  // Day 1 part 2 answer
  std::print("{0}\n", calculateFirstBasement(argv[1]));
  return 0;
}

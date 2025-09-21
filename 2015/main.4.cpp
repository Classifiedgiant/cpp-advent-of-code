#include <cassert>
#include <iomanip>
#include <openssl/md5.h>
#include <print>
#include <sstream>
#include <string>

int findNZeros(const std::string &key, const int zeroCount) {

  u_int32_t counter{0};
  while (true) {
    const auto totalKey = key + std::to_string(counter);
    unsigned char digest[MD5_DIGEST_LENGTH];

    // Using deprecated MD5 function from openssl library
    // Potentially write own MD5 algo
    MD5(reinterpret_cast<const unsigned char *>(totalKey.c_str()),
        totalKey.size(), digest);

    std::stringstream ss;
    for (int i{0}; i < MD5_DIGEST_LENGTH; i++) {
      ss << std::hex << std::setw(2) << std::setfill('0')
         << static_cast<unsigned int>(digest[i]);
    }

    const auto output{ss.str()};
    bool hasZeros{true};
    for (int i{0}; i < zeroCount; i++) {
      if (output[i] != '0') {
        hasZeros = false;
        break;
      }
    }

    if (hasZeros) {
      return counter;
    }

    counter++;
  }
}

int main(int argc, const char *argv[]) {

  assert(findNZeros("abcdef", 5) == 609043);
  assert(findNZeros("pqrstuv", 5) == 1048970);
  const auto secretKey = "yzbqklnj";

  const auto fiveZeroNum = findNZeros(secretKey, 5);
  const auto sixZeroNum = findNZeros(secretKey, 6);
  std::println("{0}, {1}", fiveZeroNum, sixZeroNum);
}

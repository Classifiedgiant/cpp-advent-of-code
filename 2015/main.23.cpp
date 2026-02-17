#include <cassert>
#include <fstream>
#include <vector>
#include <print>

#include "string_util.h"

int calculateCommand(const auto& splitLines, auto& registers)
{

    const auto& reg = splitLines[1];
    int index = (reg == "a" || reg == "a,") ? 0 : 1;
    
    if (splitLines[0] == "hlf")
        registers[index] /= 2;
    else if (splitLines[0] == "tpl")
        registers[index] *= 3;
    else if (splitLines[0] == "inc")
        registers[index]++;
    else if (splitLines[0] == "jmp")
        return std::stoi(splitLines[1]);
    else if (splitLines[0] == "jie")
        return registers[index] % 2 == 0 ? std::stoi(splitLines[2]) : 1;
    else if (splitLines[0] == "jio")
        return registers[index] == 1 ? std::stoi(splitLines[2]) : 1;
    
    return 1;
}

void RunProgram(const auto& lines, auto& registers)
{
    int i {};
    while ( i < lines.size())
    {
        const auto splitLines = Shared::SplitLine(lines[i], ' ');
        i += calculateCommand(splitLines, registers);
    }
}

int main()
{
    // read the file
    std::ifstream input{"./2015/23.txt"};

    std::vector<std::string> lines{};
    std::string line;

    while (getline(input, line))
        lines.push_back(line);
    
    std::array<int, 2> registers{};

    RunProgram(lines, registers);
    const auto part1Ans {registers[1]};
    assert(part1Ans == 184);

    registers[0] = 1;
    registers[1] = 0;
    RunProgram(lines, registers);
    const auto part2Ans {registers[1]};
    assert(part2Ans == 231);


    std::println("{}, {}", part1Ans, part2Ans);
    
    return 0;
}
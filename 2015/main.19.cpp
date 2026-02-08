#include <cassert>
#include <fstream>
#include <map>
#include <print>
#include <set>
#include <string>
#include <vector>

#include "string_util.h"

using MoleculeMap = std::map<std::string, std::vector<std::string>>;

std::pair<MoleculeMap, std::string> readMapFromFile(std::ifstream&& file)
{
    if (!file.is_open())
    {
        throw std::runtime_error{"Unable to open file"};
    }

    MoleculeMap map;
    std::string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            break;
        }
        const auto splitLine = Shared::SplitLine(line, ' ');
        map[splitLine[0]].emplace_back(splitLine[2]);
    } 

    getline(file, line);
    return {map, line};
}

size_t calibrateMolecules(const MoleculeMap& moleculeMap, const std::string& medicineMolecule)
{
    std::set<std::string> solutions{};

    for (size_t i = 0; i < medicineMolecule.size(); i++)
    {
        std::vector<MoleculeMap::const_iterator> keys{};
        

        const auto oneCharVal = medicineMolecule.substr(i, 1);
        if (auto it = moleculeMap.find(oneCharVal); it != moleculeMap.end())
        {
            keys.push_back(it);
        }

        if (i+1 < medicineMolecule.size())
        {
            const auto twoCharValues = medicineMolecule.substr(i, 2);

            if (auto it = moleculeMap.find(twoCharValues); it != moleculeMap.end())
            {
                keys.push_back(it);
            }
        }
        
        for (const auto& it : keys)
        {
            for (const auto& elem : it->second)
            {
                auto replaced = medicineMolecule;
                replaced.replace(i, it->first.length(), elem);
                solutions.insert(std::move(replaced));
            }
        }
    }


    return solutions.size();
}

size_t calculateMoleculeReplacement(const MoleculeMap& moleculeMap, std::string start, const std::string& expectedOutput)
{
    auto mapComparator = [](const std::string& left, const std::string& right) {
        if (left.length() != right.length()) return left.length() > right.length();
        return left < right;
    };
    // reverse map
    std::map<std::string, std::string, decltype(mapComparator)> reverseMap;

    for (const auto& [key, values] : moleculeMap)
    {
        for (const auto& elem: values)
        {
            reverseMap.insert({elem, key});
        }
    }

    size_t steps{};
    while (start != expectedOutput)
    {
        for (const auto& [key, value]: reverseMap) 
        {
            if (size_t pos = start.find(key);
            pos != std::string::npos)
            {
                start.replace(pos, key.length(), value);
                steps++;
                break;
            }
        }
    }

    return steps;

}

int main()
{
    const auto [molecules, input] = readMapFromFile(std::ifstream{"./2015/19.txt"});

    const auto part1Ans = calibrateMolecules(molecules, input);
    assert(part1Ans == 535);

    MoleculeMap testMap {
        { "e", {"H", "O"}},
        { "H", {"HO", "OH"}},
        { "O", {"HH"}},
    };
    assert(calculateMoleculeReplacement(testMap, "HOH", "e") == 3);
    assert(calculateMoleculeReplacement(testMap, "HOHOHO", "e") == 6);

    const auto part2Ans = calculateMoleculeReplacement(molecules, input, "e");
    assert(part2Ans == 212);

    std::println("{}, {}", part1Ans, part2Ans);
}
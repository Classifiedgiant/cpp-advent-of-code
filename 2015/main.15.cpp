#include <cassert>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <fstream>
#include <ranges>
#include <print>

#include "string_util.h"

struct IngredientProperties {
    int8_t capacity;
    int8_t durability;
    int8_t flavor;
    int8_t texture;
    int8_t calories;
    };

using Ingredients = std::pmr::unordered_map<std::string, IngredientProperties>;

Ingredients readIngredientsFromFile(std::ifstream& file) {
    if (!file.is_open()) {
        throw std::runtime_error("File cannot be opened");
    }

    Ingredients ingredients{};

    std::string line;
    while (getline(file, line)) {
        auto splitLine = Shared::SplitLine(line, ' ');
        auto ingredientName = splitLine[0].substr(0, splitLine[0].length() - 1);
        ingredients.emplace(
            ingredientName,
            IngredientProperties{
                .capacity = static_cast<int8_t>(stoi(splitLine[2])),
                .durability = static_cast<int8_t>(stoi(splitLine[4])),
                .flavor = static_cast<int8_t>(stoi(splitLine[6])),
                .texture = static_cast<int8_t>(stoi(splitLine[8])),
                .calories = static_cast<int8_t>(stoi(splitLine[10]))
            });
    }

    return ingredients;
}

long long calculateScore(
    const std::vector<int32_t>& teaspoonsPerIngredient,
    const Ingredients& ingredients,
    const std::optional<int> desiredCalories) {

    long long capacity{0};
    long long durability{0};
    long long flavor{0};
    long long texture{0};
    long long calories{0};

    for (const auto& [teaspoonCount, ingredientEntry] : std::views::zip(teaspoonsPerIngredient, ingredients)) {
        const auto& props = ingredientEntry.second;
        capacity += teaspoonCount * props.capacity;
        durability += teaspoonCount * props.durability;
        flavor += teaspoonCount * props.flavor;
        texture += teaspoonCount * props.texture;
        calories += teaspoonCount * props.calories;
    }

    capacity = std::max(0LL, capacity);
    durability = std::max(0LL, durability);
    flavor = std::max(0LL, flavor);
    texture = std::max(0LL, texture);

    if (desiredCalories.has_value() && desiredCalories != calories)
        return 0;

    return capacity * durability * flavor * texture;
}

long long findBestCombination(
    std::vector<int32_t>& teaspoonsPerIngredient,
    const Ingredients& ingredients,
    int index,
    int teaspoonsLeft,
    const std::optional<int> desiredCalories) {

    // if we are at the last point
    // all the teaspoons can just go he
    if (index == ingredients.size() - 1) {
        teaspoonsPerIngredient[index] = teaspoonsLeft;
        return calculateScore(teaspoonsPerIngredient, ingredients, desiredCalories);
    }

    long long maxScore = 0;
    for (int i = teaspoonsLeft; i >= 0; i--) {
        teaspoonsPerIngredient[index] = i;
        const auto score = findBestCombination(teaspoonsPerIngredient, ingredients, index + 1, teaspoonsLeft - i, desiredCalories);
        maxScore = std::max(maxScore, score);
    }

    return maxScore;
}

int main(int argc, const char* argv[]) {
    auto inputStream = std::ifstream{"./2015/15.txt"};

    const auto ingredients = readIngredientsFromFile(inputStream);

    std::vector teaspoonsPerIngredient(ingredients.size(), 0);
    const auto bestCookieScore = findBestCombination(teaspoonsPerIngredient, ingredients, 0, 100, {});
    assert(bestCookieScore == 21367368);

    const auto best500CalorieCookieScore = findBestCombination(teaspoonsPerIngredient, ingredients, 0, 100, 500);
    assert(best500CalorieCookieScore == 1766400);
    std::println("{0}, {1}", bestCookieScore, best500CalorieCookieScore);
}

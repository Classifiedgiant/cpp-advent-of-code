#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <limits>
#include <print>
#include <ranges>
#include <vector>

struct PlayerData
{
    constexpr static PlayerData CreatePlayer() { return PlayerData{.hitPoints = 50, .armour = 0, .mana = 500};}
    int hitPoints;
    int armour;
    int mana;
};

struct BossData
{
    constexpr static BossData CreateBoss() { return {.hitPoints = 58, .damage = 9};}
    int hitPoints;
    int damage;
};

enum class SpellType
{
    Missle,
    Drain,
    Shield,
    Poison,
    Recharge
};

struct SpellData
{
    SpellType type;
    int cost;
    int damage;
    int hitPoints;
    int armour;
    int mana;
    int duration; // 0 = instant
};

struct GameState
{
    int spentMana;
    bool isPlayerTurn;
    PlayerData player;
    BossData boss;
    std::vector<SpellData> activeSpells;
};

constexpr std::array<SpellData, 5> spells =
{
    SpellData{SpellType::Missle, 53, 4, 0, 0, 0, 0},
    SpellData{SpellType::Drain, 73, 2, 2, 0, 0, 0},
    SpellData{SpellType::Shield, 113, 0, 0, 7, 0, 6},
    SpellData{SpellType::Poison, 173, 3, 0, 0, 0, 6},
    SpellData{SpellType::Recharge, 229, 0, 0, 0, 101, 5}
};

void applyGameStates(GameState& gameState) {
    //  apply any effects
    const auto applySpells = [&gameState](auto& elem)
    {
        switch(elem.type)
        {
            case SpellType::Shield:
                gameState.player.armour = elem.armour;
                break;

            case SpellType::Poison:
                gameState.boss.hitPoints -= elem.damage;
                break;

            case SpellType::Recharge:
                gameState.player.mana += elem.mana;
                break;

            default:
                throw std::runtime_error{"Unknown Type"};
        }

        elem.duration--;
    };

    std::for_each(begin(gameState.activeSpells), end(gameState.activeSpells), applySpells);
    std::erase_if(gameState.activeSpells, [&gameState](const auto& elem)
    {
        if (elem.duration == 0 && elem.type == SpellType::Shield)
        {
            gameState.player.armour = 0;
        }
        return elem.duration == 0;
    });
}

void calculateNextStep(GameState gameState, int manaSpent, int& minMana, bool isHardMode)
{
    if (isHardMode && gameState.isPlayerTurn)
    {
        gameState.player.hitPoints--;
    }

    applyGameStates(gameState);
    if (gameState.player.hitPoints <= 0 || gameState.boss.hitPoints <= 0)
    {
        if (gameState.boss.hitPoints <= 0)
        {
            minMana = std::min(manaSpent, minMana);
        }
        return;
    }

    if (manaSpent > minMana)
        return;

    if (gameState.isPlayerTurn)
    {
        if (std::all_of(begin(spells), end(spells), [&](const auto& spell){ return spell.cost > gameState.player.mana; }))
        {
            return;
        }
        
        for (const auto spell : spells)
        {
            if (spell.cost > gameState.player.mana)
            {
                continue;
            }
            if (std::find_if(begin(gameState.activeSpells), end(gameState.activeSpells), [&spell](const auto& elem) { return elem.type == spell.type;}) != gameState.activeSpells.end())
            {
                continue;
            }

            auto nextState = gameState;
            switch (spell.type)
            {
                case SpellType::Missle:
                    nextState.boss.hitPoints -= spell.damage;
                    break;

                case SpellType::Drain:
                    nextState.player.hitPoints += spell.hitPoints;
                    nextState.boss.hitPoints -= spell.damage;
                    break;

                case SpellType::Recharge:
                case SpellType::Poison:
                case SpellType::Shield:
                    nextState.activeSpells.push_back(spell);
                    break;

                default:
                    std::runtime_error{"Wrong Spell Type"};
            }

            nextState.player.mana -= spell.cost;

            nextState.isPlayerTurn = !nextState.isPlayerTurn;
            calculateNextStep(nextState, manaSpent + spell.cost, minMana, isHardMode);
        }
    }
    else
    {
        gameState.player.hitPoints -= std::max(gameState.boss.damage - gameState.player.armour, 1);
        gameState.isPlayerTurn = !gameState.isPlayerTurn;
        calculateNextStep(gameState, manaSpent, minMana, isHardMode);
    }
}

int main()
{
    int smallestManaSpent = std::numeric_limits<int>::max();

    GameState baseState
    {
        .spentMana = {},
        .isPlayerTurn = true,
        .player = PlayerData::CreatePlayer(),
        .boss = BossData::CreateBoss(),
        .activeSpells = {}
    };

    auto isHardMode {false};
    calculateNextStep(baseState, 0, smallestManaSpent, isHardMode);
    const auto part1Ans = smallestManaSpent;
    assert(part1Ans == 1269);


    isHardMode = true;
    smallestManaSpent = std::numeric_limits<int>::max();
    calculateNextStep(baseState, 0, smallestManaSpent, isHardMode);
    const auto part2Ans = smallestManaSpent;
    assert(part2Ans == 1309);

    std::println("{}, {}", part1Ans, part2Ans);

}
#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
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

struct SpellData
{
    int cost;
    int damage;
    int hitpoints;
    int armour;
    int mana;
    int duration; // 0 = instant
};

constexpr std::array<SpellData, 5> spells =
{
    SpellData{53, 4, 0, 0, 0, 0},
    SpellData{73, 2, 2, 0, 0, 0},
    SpellData{113, 0, 0, 7, 0, 6},
    SpellData{173, 3, 0, 0, 0, 6},
    SpellData{229, 0, 0, 0, 101, 5}
};

constexpr int calculateTimeToKill(const SpellData& spell, int hitPoints)
{
    if (spell.duration == 0)
    {
        return (spell.damage + hitPoints - 1) / spell.damage;
    }
    return -1;

    // duration spell
    return ((spell.damage * s)
}

int calculateMinimumManaUsage()
{
    const auto player = PlayerData::CreatePlayer();
    const auto boss = BossData::CreateBoss();
    for (const auto& spell : spells)
    {
        // int turnsToKill = (spell.damage * std::max(spell.duration, 1)) / boss.hitPoints;
        // int turnToBeKilled = (boss.damage) / 
    }

}

int main()
{
    static_assert(calculateTimeToKill(spells[0], 4) == 1);
    static_assert(calculateTimeToKill(spells[0], 5) == 2);
    static_assert(calculateTimeToKill(spells[3], 7) == 1);
    calculateMinimumManaUsage();
}
#include <array>
#include <cassert>
#include <limits>
#include <print>

struct ItemData
{
    int cost;
    int damage;
    int armor;
};

struct PlayerData
{
    static PlayerData CreatePlayer(
        const ItemData& weapons,
        const ItemData& armor,
        const ItemData* ring1,
        const ItemData* ring2)
    {
        int cost = weapons.cost + armor.cost;
        auto damageVal = weapons.damage + armor.damage;
        auto armorVal = weapons.armor + armor.armor;

        if (ring1)
        {
            cost += ring1->cost;
            damageVal += ring1->damage;
            armorVal += ring1->armor;
        }

        if (ring2)
        {
            cost += ring2->cost;
            damageVal += ring2->damage;
            armorVal += ring2->armor;
        }

        return PlayerData{.equipmentCost = cost, .hitPoints = 100, .damage = damageVal, .armor = armorVal};
    }

    static PlayerData CreateBoss()
    {
        return PlayerData{.equipmentCost = 0, .hitPoints = 103, .damage = 9, .armor = 2};
    }

    int equipmentCost;
    int hitPoints;
    int damage;
    int armor;
};

static constexpr std::array<ItemData, 5> Weapons = {
    ItemData{8, 4, 0},
    ItemData{10, 5, 0},
    ItemData{25, 6, 0},
    ItemData{40, 7, 0},
    ItemData{74, 8, 0}
};

static constexpr std::array<ItemData, 6> Armors = {
    ItemData{0, 0, 0}, // fakes no armour
    ItemData{13, 0, 1},
    ItemData{31, 0, 2},
    ItemData{53, 0, 3},
    ItemData{75, 0, 4},
    ItemData{102, 0, 5}
};

static constexpr std::array<ItemData, 6> Rings = {
    ItemData{25, 1, 0},
    ItemData{50, 2, 0},
    ItemData{100, 3, 0},
    ItemData{20, 0, 1},
    ItemData{40, 0, 2},
    ItemData{80, 0, 3}
};

bool DoesPlayerWin(PlayerData player, PlayerData boss)
{
    PlayerData* curr = &player;
    PlayerData* other = &boss;

    while (true)
    {
        other->hitPoints -= std::max(curr->damage - other->armor, 1);
        if (other->hitPoints <= 0)
        {
            return curr == &player;
        }
        std::swap(curr, other);
    }
}

int IsExpectedOutcome(const bool playerToWin, PlayerData playerData, PlayerData bossData, int maxGold)
{
    if (DoesPlayerWin(playerData, bossData) == playerToWin)
    {
        maxGold = playerToWin ? std::min(maxGold, playerData.equipmentCost) : std::max(maxGold, playerData.equipmentCost);
    }

    return maxGold;
}

int PermuteAllEquipment(const bool playerWinFight)
{
    int gold = playerWinFight ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min();

    for (const auto& weapon: Weapons)
    {
        for (const auto& armour: Armors)
        {
            // weapon + armour + no rings
            gold = IsExpectedOutcome(
                playerWinFight,
                PlayerData::CreatePlayer(weapon, armour, nullptr, nullptr),
                PlayerData::CreateBoss(),
                gold);

            for (size_t i{}; i < Rings.size(); i++)
            {
                for (size_t j{i}; j < Rings.size(); j++)
                {
                    if (i == j)
                    {
                        gold = IsExpectedOutcome(
                            playerWinFight,
                            PlayerData::CreatePlayer(weapon, armour, &Rings[i], nullptr),
                            PlayerData::CreateBoss(),
                            gold);
                    }
                    else
                    {
                        gold = IsExpectedOutcome(
                            playerWinFight,
                            PlayerData::CreatePlayer(weapon, armour, &Rings[i], &Rings[j]),
                            PlayerData::CreateBoss(),
                            gold);
                    }
                }
            }
        }
    }

    return gold;
}

int main()
{
    const auto lowestGold = PermuteAllEquipment(true);
    assert(lowestGold == 121);

    const auto highestGold = PermuteAllEquipment(false);
    assert(highestGold == 201);

    std::println("{}, {}", lowestGold, highestGold);
    return 0;
}
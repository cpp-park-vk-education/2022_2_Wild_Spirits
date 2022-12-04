#include <gmock/gmock.h>

#include "StatBased.hpp"
#include "Dice.hpp"
#include "DamageTypeStorage.hpp"
#include "Resistible.hpp"

namespace DnD {
TEST(StatTest, ValidStatBonus) {
    StatBased stats({
        {"dex", 12},
        {"str", 11},
        {"int", 9},
        {"cha", 14},
        {"cns", 7}
    });

    std::cout << -1 / 2 << '\n';

    ASSERT_EQ(stats.statBonus("dex"), 1);
    ASSERT_EQ(stats.statBonus("str"), 0);
    ASSERT_EQ(stats.statBonus("int"), -1);
    ASSERT_EQ(stats.statBonus("cha"), 2);
    ASSERT_EQ(stats.statBonus("cns"), -2);
}

TEST(DiceSuite, Validation) {  // cppcheck-suppress [syntaxError]
    Dice dice;
    std::vector<uint8_t> valid_dice = {4, 6, 8, 10, 12, 20};

    for (auto die : valid_dice) {
        ASSERT_TRUE(dice.isValid(die));
    }

    EXPECT_FALSE(dice.isValid(0));
    EXPECT_FALSE(dice.isValid(-5));
    EXPECT_FALSE(dice.isValid(9));
    EXPECT_FALSE(dice.isValid(3));
}

TEST(DamageTypesStorageSuite, ItIsCreatedCorrectly) {
    DamageTypeStorage types;
    std::unordered_set<uint8_t> expected_unused;
    for (size_t i = DamageTypeStorage::defaultNum(); i < DamageTypeStorage::maxNum(); ++i) {
        expected_unused.insert(i);
    }
    ASSERT_EQ(types.unused_ids_, expected_unused);
}

TEST(DamageTypesStorageSuite, ItManagesIds) {
    DamageTypeStorage types;

    auto [id, status] = types.addDamageType("a");
    ASSERT_TRUE(status.ok());

    auto [name, err_status] = types.typeName(id);
    ASSERT_TRUE(err_status.ok());
    ASSERT_EQ(name, "a");

    err_status = types.removeDamageType(id);
    ASSERT_TRUE(err_status.ok());

    auto [_, err_status2] = types.typeName(id);
    ASSERT_FALSE(err_status2.ok());

    for (size_t i = DamageTypeStorage::defaultNum(); i < DamageTypeStorage::maxNum(); ++i) {
        auto [_, status] = types.addDamageType(std::to_string(i));
        ASSERT_TRUE(status.ok());
    }

    std::cout << "EMPTY: " << std::boolalpha << types.filled() << '\n';

    std::tie(id, status) = types.addDamageType("b");
    ASSERT_FALSE(status.ok());

    types.removeDamageType(DamageTypeStorage::defaultNum() + 1);

    std::tie(id, status)  = types.addDamageType("b");
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(id, DamageTypeStorage::defaultNum() + 1);
}

TEST(ResistibleSuite, ItWorks) {
    Resistible res;
    ASSERT_FALSE(res.isVulnerableTo(0));

    res.addResistance(0);
    ASSERT_TRUE(res.isResistantTo(0));
    ASSERT_FALSE(res.isVulnerableTo(0));

    res.removeResistance(0);
    ASSERT_FALSE(res.isResistantTo(0));

    ASSERT_FALSE(res.isVulnerableTo(3));
    res.addVulnerability(3);
    ASSERT_TRUE(res.isVulnerableTo(3));

    res.removeVulnerability(3);
    ASSERT_FALSE(res.isVulnerableTo(3));
}
}  // namespace DnD

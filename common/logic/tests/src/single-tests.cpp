#include <gmock/gmock.h>

#include "StatBased.hpp"
#include "Dice.hpp"
#include "DamageTypes.hpp"
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

TEST(DamageTypesSuite, ItWorks) {
    DamageTypeStorage types;

    auto [id, err] = types.addDamageType("a");
    ASSERT_TRUE(err.ok());
    ASSERT_EQ(types.typeName(id), "a");

    types.removeDamageType(id);
    ASSERT_EQ(types.typeName(id), "");

    for (size_t i = 0; i < DamageTypeStorage::maxNum(); ++i) {
        auto [_, status] = types.addDamageType(std::to_string(i));
        ASSERT_TRUE(status.ok());
    }

    auto [_, status] = types.addDamageType("b");
    ASSERT_FALSE(status.ok());

    types.removeDamageType(0);

    auto [b_id, status] = types.addDamageType("b");
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(b_id, 0);
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

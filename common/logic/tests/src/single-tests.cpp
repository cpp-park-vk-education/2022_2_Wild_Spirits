#include <gmock/gmock.h>

#include "StatBased.hpp"
#include "Dice.hpp"
#include "DamageTypes.hpp"
#include "Resistible.hpp"

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

TEST(DiceSuite, Validation) {
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
    DamageTypes types;

    types.addDamageType("a");
    ASSERT_NE(types.id("a"), -1);
    ASSERT_EQ(types.typeName(types.id("a")), "a");

    types.removeDamageType("a");
    ASSERT_EQ(types.id("a"), -1);

    for (size_t i = 0; i < DamageTypes::maxNum(); ++i) {
        std::string dmg_type = "a" + std::to_string(i);
        auto status = types.addDamageType(dmg_type);
        ASSERT_TRUE(status.ok());
    }

    auto status = types.addDamageType("b");
    ASSERT_FALSE(status.ok());

    types.removeDamageType("a4");

    status = types.addDamageType("b");
    ASSERT_TRUE(status.ok());
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

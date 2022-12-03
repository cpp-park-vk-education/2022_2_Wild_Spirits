#include <gmock/gmock.h>

#include "action-suites.hpp"

#include "Damage.hpp"

using ::testing::Return;
using ::testing::_;

namespace DnD {
TEST_F(EffectSuite, HealReturnsValidResult) {
    const unsigned int amount = 5;
    Heal heal(amount);
    heal.updateActionResult(character, &new_result);

    ASSERT_EQ(result.hp + amount, new_result.hp);
}

TEST_F(EffectSuite, MoveReturnsValidResult) {  // cppcheck-suppress [syntaxError]
    const Tile tile = {1, 3};
    Move move(1, 3);
    move.updateActionResult(character, &new_result);

    ASSERT_EQ(result.pos, new_result.pos + tile);
}

TEST_F(DamageSuite, DealDamageConsidersResists) {
    EXPECT_CALL((*dice), roll(_))
        .WillRepeatedly(Return(6));

    DealDamage damage_resist(0, 6, 2, std::move(dice));
    damage_resist.updateActionResult(character, &new_result);
    ASSERT_EQ(result.hp - 6, new_result.hp);
}

TEST_F(DamageSuite, DealDamageConsidersVulnerabilities) {
    EXPECT_CALL(*dice, roll(_))
        .WillRepeatedly(Return(3));

    DealDamage damage(1, 6, 2, std::move(dice));
    damage.updateActionResult(character, &new_result);
    ASSERT_EQ(result.hp - 12, new_result.hp);
}

TEST(DiceSuite, ThrowsOnInvalidDice) {
    ASSERT_FALSE(Dice().isValid(-3));
    ASSERT_THROW(DealDamage(0, 7, 2, std::make_unique<Dice>()), InvalidDice);
    ASSERT_THROW(DealDamage(0, -1, 2, std::make_unique<Dice>()), InvalidDice);
}
}  // namespace DnD

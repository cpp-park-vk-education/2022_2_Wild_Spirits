#include <gmock/gmock.h>

#include "Activatable.hpp"
#include "Buff.hpp"
#include "Damage.hpp"
#include "CharacterInstance.hpp"
#include "GameState.hpp"
#include "TurnOrder.hpp"

#include "action-suites.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::SizeIs;

TEST_F(ActionSuite, SingleActionTest) {
    // Add buff to npc's dex, check if it will dodge action
    location.npc().get(2).addBuff(Buff({{"dex", 4}}, 1));

    // Action checks enemies dex by default,
    // they have armor class of 10 by default, which is summed with dex bonus ((14 - 10) / 2 == 2)
    // equaling 12

    // Damage rolls
    EXPECT_CALL(*dice, roll(4))
        .WillOnce(Return(1))  // enemy 1
        .WillOnce(Return(2))
        .WillOnce(Return(3))  // enemy 3
        .WillOnce(Return(2))
        .WillOnce(Return(4))  // enemy 5
        .WillOnce(Return(3));

    // Assume player rolled 11 when he used this action,
    // and got 2 points as a bonus from his stats, totalling 13
    auto [results, error_status] = action.getResults(character, Tile{2, 1}, 13);

    ASSERT_TRUE(error_status.ok());
    ASSERT_THAT(results, SizeIs(3));

    std::vector<size_t> enemies_hit = {1, 3, 5};

    for (size_t i = 0; i < results.size(); ++i) {
        ASSERT_EQ(results[i], Action::Result(
                                enemies_hit[i],
                                Tile{1, 2}, -2 - i,
                                {Buff({ {"str", -2}, {"dex", -1} }, 2)}));
    }

    // Assert that cast on invalid range returns failure
    std::tie(results, error_status) = action.getResults(character, Tile{3, 1}, 13);
    ASSERT_FALSE(error_status.ok());
}

TEST_F(ActivatableSuite, PlayerSpellTest) {
    Spell spell(0, "", 0, {action, heal_action}, 5, "int", 2);
    player.spells().add(&spell);

    auto result_buff = Buff({ {"str", -2}, {"dex", -1} }, 2);

    // Let player roll 20 to hit both enemies
    MockDice player_die;
    EXPECT_CALL(player_die, roll(20))
        .WillOnce(Return(20));

    auto player_use_spell = [&] {
        return player.use("spell", 0,
                              { Tile{4, 1}, player.mapPosition().first }, &player_die);
    };

    // Damage rolls
    EXPECT_CALL(*dice, roll(4))
        .WillOnce(Return(3))  // enemy 3
        .WillOnce(Return(2))
        .WillOnce(Return(4))  // enemy 4
        .WillOnce(Return(3));

    std::vector<Action::Result> expected_results = {
        {3, Tile{4, 4}, 5, { result_buff }},
        {4, Tile{4, 3}, 3, { result_buff }},
        {player.id(), Tile{2, 2}, 8, {}}
    };

    player.setMaxSpellPoints(5);
    player.refreshSpellPoints();
    char_template_.setMaxActionPoints(10);
    player.refreshActionPoints();

    auto [results, error_status] = player_use_spell();

    ASSERT_TRUE(error_status.ok());
    ASSERT_EQ(player.actionPoints(), 5);
    ASSERT_EQ(player.spellPoints(), 3);
    ASSERT_EQ(results, expected_results);

    // Cast spell with less action points than required
    player.setActionPoints(4);
    std::tie(results, error_status) = player_use_spell();
    ASSERT_FALSE(error_status.ok());

    // Cast spell with less spell points than required
    player.setActionPoints(6);
    player.setSpellPoints(1);
    std::tie(results, error_status) = player_use_spell();
    ASSERT_FALSE(error_status.ok());
}

TEST_F(ActivatableSuite, PlayerConsumableTest) {
    player.consumables().add(0, "", 0, std::vector<Action>{ heal_action }, 1, 2);
    auto& item = player.consumables().get(0);

    player.use("consumable", 0, {player.mapPosition().first});
    ASSERT_EQ(item.usesLeft(), 1);

    player.use("consumable", 0, {player.mapPosition().first});
    ASSERT_TRUE(item.empty());
}

TEST(ArmorSuite, ArmorClassDependsOnType) {
    MockGameMap map;
    Character player_template;
    PlayerCharacter player(0, player_template, PositionFactory::create({0, 0}), map, Class(), Race());
    player_template.setStat("dex", 18);  // Bonus to dex is 4

    Armor armor(0, "", 0, 0, 10, Armor::Type::Light);
    player.setArmor(armor);
    ASSERT_EQ(player.armorClass(), 14);

    armor.setArmorType(Armor::Type::Medium);  // Medium armor gains 2 points maximum from dex
    ASSERT_EQ(player.armorClass(), 12);

    armor.setArmorType(Armor::Type::Heavy);  // Heavy armor gains no bonuses from dex
    ASSERT_EQ(player.armorClass(), 10);
}

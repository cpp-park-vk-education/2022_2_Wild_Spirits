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

namespace DnD {
TEST_F(ActionSuite, SingleActionTest) {
    // Add buff to npc's dex, check if it will dodge action
    locations.get(0).npc().get(2).addBuff(Buff({{"dex", 4}}, 1));

    locations.get(0).npc().each([] (auto& c) { std::cout << std::boolalpha << c.isHostile() << '\n'; });
    std::cout << locations.get(0).npc().size() << '\n';

    // Action checks enemies dex by default,
    // they have armor class of 10 by default, which is summed with dex bonus ((14 - 10) / 2 == 2)
    // equaling 12

    // Damage rolls
    EXPECT_CALL(*dice_ptr, roll(4, 2))
        .WillOnce(Return(std::vector<uint8_t>{1, 2}))
        .WillOnce(Return(std::vector<uint8_t>{3, 2}))
        .WillOnce(Return(std::vector<uint8_t>{4, 3}));

    // Assume player rolled 11 when he used this action,
    // and got 2 points as a bonus from his stats, totalling 13
    auto [results, error_status] = action.getResults(*character, Tile{2, 1}, 13);

    ASSERT_EQ(error_status, ErrorStatus::OK);
    ASSERT_THAT(results, SizeIs(3));

    std::set<size_t> enemies_hit = {1, 3, 5};
    std::vector<int> expected_hp_loss = {-3, -5, -7};
    std::vector<std::vector<Dice::Roll>> expected_dice_rolls = {
        {Dice::Roll{4, 1}, Dice::Roll{4, 2}},
        {Dice::Roll{4, 3}, Dice::Roll{4, 2}},
        {Dice::Roll{4, 4}, Dice::Roll{4, 3}}
    };

    std::vector<Action::Result> expected_results;
    expected_results.reserve(results.size());

    auto& location = locations.get(0);
    size_t i = 0;
    for (const auto& [_, npc] : location.npc()) {
        if (enemies_hit.contains(npc->id())) {
             expected_results.emplace_back(
                                      npc->id(),
                                      Tile{1, 2}, expected_hp_loss[i],
                                      std::list<Buff>{Buff({ {"str", -2}, {"dex", -1} }, 2)},
                                      expected_dice_rolls[i]);
            ++i;
        }
    }

    EXPECT_EQ(results, expected_results);

    // Assert that cast on invalid range returns failure
    std::tie(results, error_status) = action.getResults(*character, Tile{3, 1}, 13);
    ASSERT_EQ(error_status, ErrorStatus::INVALID_CAST_RANGE);
}

TEST_F(ActivatableSuite, PlayerSpellTest) {  // cppcheck-suppress [syntaxError]
    auto& player = map.players().get(8);

    player.resetHP();
    player.takeDamage(5);

    std::vector<Action> actions;
    actions.reserve(2);

    actions.push_back(std::move(action));
    actions.push_back(std::move(heal_action));

    auto spell = std::make_shared<Spell>(0, "", 0, std::move(actions), 5, "int", 2);
    player.spells().add(spell);
    player.moveBy(2, 0);

    auto result_buff = Buff({ {"str", -2}, {"dex", -1} }, 2);

    // Let player roll 20 to hit both enemies
    MockDice player_die;
    EXPECT_CALL(player_die, roll(20))
        .WillRepeatedly(Return(20));

    auto player_use_spell = [&] {
        return player.use("spell", 0, { Tile{4, 1}, player.mapPosition()[0] }, &player_die);
    };

    // Damage rolls
    EXPECT_CALL(*dice_ptr, roll(4, 2))
        .WillOnce(Return(std::vector<uint8_t>{3, 2}))
        .WillOnce(Return(std::vector<uint8_t>{4, 3}));

    player.setMaxSpellPoints(5);
    player.refreshSpellPoints();

    char_template_->setMaxActionPoints(10);
    player.refreshActionPoints();

    std::vector<unsigned int> expected_enemy_hp = {5, 3};

    std::vector<std::vector<Dice::Roll>> expected_dice_rolls = {
        {Dice::Roll{4, 3}, Dice::Roll{4, 2}},
        {Dice::Roll{4, 4}, Dice::Roll{4, 3}}
    };

    std::set<size_t> enemies_hit = {3, 4};

    std::vector<Action::Result> action_results;
    action_results.reserve(3);

    size_t i = 0;
    for (auto& [_, npc] : locations.get(0).npc()) {
        if (enemies_hit.contains(npc->id())) {
            action_results.emplace_back(npc->id(),
                                        Tile{4, 3},
                                        expected_enemy_hp[i],
                                        std::list<Buff>{ result_buff },
                                        expected_dice_rolls[i]);
            ++i;
        }
    }

    action_results.emplace_back(player.id(), Tile{4, 2}, 8, std::list<Buff>{});

    Activatable::Result expected_results = { 5, 2, action_results };

    auto [results, error_status] = player_use_spell();

    ASSERT_EQ(error_status, ErrorStatus::OK);
    EXPECT_EQ(player.actionPoints(), 5);
    EXPECT_EQ(player.spellPoints(), 3);
    ASSERT_EQ(results, expected_results);

    // Cast spell with less action points than required
    player.setActionPoints(4);
    std::tie(results, error_status) = player_use_spell();
    ASSERT_EQ(error_status, ErrorStatus::NO_ACTION_POINTS);

    // Cast spell with less spell points than required
    player.setActionPoints(6);
    player.setSpellPoints(1);
    std::tie(results, error_status) = player_use_spell();
    ASSERT_EQ(error_status, ErrorStatus::NO_SPELL_POINTS);
}

TEST_F(ActivatableSuite, PlayerConsumableTest) {
    auto& player = map.players().get(8);

    auto base_item = std::make_shared<ActivatableItem>(0, "", 0, std::vector<Action>{ heal_action }, 1);
    player.consumables().add(Consumable{base_item, 2});
    auto& item = player.consumables().get(0);

    player.use("consumable", 0, { player.mapPosition()[0] });
    ASSERT_EQ(item.usesLeft(), 1);

    player.use("consumable", 0, { player.mapPosition()[0] });
    ASSERT_TRUE(item.empty());
}

TEST(ArmorSuite, ArmorClassDependsOnType) {
    MockGameMap map;
    Storage<CharacterInstance*> characters;

    EXPECT_CALL(map, allCharacters())
        .WillRepeatedly(::testing::ReturnRef(characters));

    PlayerCharacter player(0, Character(), PositionFactory::create({0, 0}), map,
                              std::make_shared<Class>(), std::make_shared<Race>());

    player.original().setStat("dex", 18);  // Bonus to dex is 4

    auto armor = std::make_shared<Armor>(0, "", 0, 0, 11, Armor::Type::Light);
    player.setArmor(armor);
    EXPECT_EQ(player.armorClass(), 15);

    armor->setArmorType(Armor::Type::Medium);  // Medium armor gains 2 points maximum from dex
    EXPECT_EQ(player.armorClass(), 13);

    armor->setArmorType(Armor::Type::Heavy);  // Heavy armor gains no bonuses from dex
    EXPECT_EQ(player.armorClass(), 11);
}
}  // namespace DnD

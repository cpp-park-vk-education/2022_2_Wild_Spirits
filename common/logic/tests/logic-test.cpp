#include <gmock/gmock.h>

#include "Activatable.hpp"
#include "Damage.hpp"
#include "CharacterInstance.hpp"
#include "Armor.hpp"
#include "GameState.hpp"

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;
using ::testing::SizeIs;

class AreaSuite : public ::testing::Test {
 protected:
    Tile target_ = {5, 2};
};

TEST_F(AreaSuite, PointAreaWorks) {
    PointArea area;
    area.setTarget(target_);

    ASSERT_TRUE(area.isInArea(target_));

    ASSERT_FALSE(area.isInArea(Tile{4, 2}));
    ASSERT_FALSE(area.isInArea(Tile{5, 3}));
}


TEST_F(AreaSuite, RectAreaWorks) {
    RectangularArea area(1, 2);
    area.setTarget(target_);

    ASSERT_TRUE(area.isInArea(target_));
    ASSERT_TRUE(area.isInArea(target_ + Tile{1, 1}));
    ASSERT_TRUE(area.isInArea(target_ - Tile{1, 2}));

    ASSERT_FALSE(area.isInArea(target_ + Tile{2, 2}));
    ASSERT_FALSE(area.isInArea(target_ - Tile{1, 3}));
}

TEST_F(AreaSuite, CustomAreaWorks) {
    std::vector<Tile> tiles = {Tile{1, 2}, Tile{-1, 3}, Tile{4, 0}};
    CustomArea area(tiles);

    area.setTarget(target_);

    for (const auto& tile : tiles) {
        ASSERT_TRUE(area.isInArea(target_ + tile));
    }

    ASSERT_FALSE(area.isInArea(target_ + Tile{1, 3}));
    ASSERT_FALSE(area.isInArea(target_ - Tile{1, 0}));
}

TEST(PositionSuite, TilePosAreaCheck) {
    TilePos pos(5, 7);

    PointArea p_area;
    p_area.setTarget(pos.mapPosition().first);
    ASSERT_TRUE(pos.isInArea(p_area));
    ASSERT_EQ(pos.isInArea(p_area), p_area.isInArea(pos.mapPosition().first));

    RectangularArea r_area(2, 2);
    r_area.setTarget(Tile{4, 6});
    ASSERT_TRUE(pos.isInArea(r_area));
    ASSERT_EQ(pos.isInArea(r_area), r_area.isInArea(pos.mapPosition().first));

    CustomArea c_area({{1, 2}, {0, 2}, {3, -1}});
    c_area.setTarget(Tile{2, 8});
    ASSERT_TRUE(pos.isInArea(c_area));
    ASSERT_EQ(pos.isInArea(c_area), c_area.isInArea(pos.mapPosition().first));
}

TEST(PositionSuite, RectPosAreaCheck) {
    RectangularPos pos(Tile{0, 3}, Tile{2, 1});

    PointArea p_area;
    p_area.setTarget(Tile{1, 4});
    ASSERT_TRUE(pos.isInArea(p_area));

    p_area.setTarget(Tile{1, 2});
    ASSERT_FALSE(pos.isInArea(p_area));

    RectangularArea r_area(1, 1);
    r_area.setTarget(Tile{3, 2});
    ASSERT_TRUE(pos.isInArea(r_area));
}

class MockGameMap : public GameMap {
 public:
    MockGameMap() = default;

    MOCK_METHOD(void, addLocation, (size_t, const Location&), (override));
    MOCK_METHOD(void, removeLocation, (size_t), (override));
    MOCK_METHOD(void, switchLocation, (size_t), (override));
    MOCK_METHOD(void, switchLocation, (size_t, size_t), (override));
    MOCK_METHOD(Location&, currentLocation, (), (override));
    MOCK_METHOD(size_t, currentLocationId, (), (const, override));
    MOCK_METHOD(Storage<PlayerCharacter>&, players, ());
    MOCK_METHOD(const Location&, getLocation, (size_t), (const, override));
};

class MockDice : public DiceInterface {
 public:
    MOCK_METHOD(uint8_t, roll, (uint8_t), (const, override));
    MOCK_METHOD(std::vector<uint8_t>, roll, (uint8_t, size_t), (const, override));
    DiceInterface* clone() const override {
        return new MockDice();
    }
};

class EffectSuite : public ::testing::Test {
 protected:
    Character char_template_;
    MockGameMap map;
    CharacterInstance character;
    Action::Result result;
    Action::Result new_result;

 public:
    EffectSuite() :
        character(7, char_template_, PositionFactory::create(Tile{1, 2}), map),
        result(0), new_result(result) {
            char_template_.addResistance(0);
            char_template_.addVulnerability(1);
    }
};

TEST_F(EffectSuite, HealReturnsValidResult) {
    const unsigned int amount = 5;
    Heal heal(amount);
    heal.updateActionResult(character, &new_result);

    ASSERT_EQ(result.hp + amount, new_result.hp);
}

TEST_F(EffectSuite, MoveReturnsValidResult) {
    const Tile tile = {1, 3};
    Move move(1, 3);
    move.updateActionResult(character, &new_result);

    ASSERT_EQ(result.pos, new_result.pos + tile);
}

class DamageSuite : public EffectSuite {
 protected:
    MockDice* dice;

 public:
    DamageSuite() : dice(new MockDice()) {}
};

TEST_F(DamageSuite, DealDamageConsidersResists) {
    EXPECT_CALL((*dice), roll(_))
        .WillRepeatedly(Return(6));

    DealDamage damage_resist(new Damage(0, 6, 2), dice);
    damage_resist.updateActionResult(character, &new_result);
    ASSERT_EQ(result.hp - 6, new_result.hp);
}

TEST_F(DamageSuite, DealDamageConsidersVulnerabilities) {
    EXPECT_CALL(*dice, roll(_))
        .WillRepeatedly(Return(3));

    DealDamage damage(new Damage(1, 6, 2), dice);
    damage.updateActionResult(character, &new_result);
    ASSERT_EQ(result.hp - 12, new_result.hp);
}

TEST(DiceSuite, ThrowsOnInvalidDice) {
    ASSERT_FALSE(Dice().isValid(-3));
    ASSERT_THROW(DealDamage(new Damage(0, 7, 2), new Dice()), InvalidDice);
    ASSERT_THROW(DealDamage(new Damage(0, -1, 2), new Dice()), InvalidDice);
}

class ActionSuite : public DamageSuite{
 protected:
    NPC test_enemy_;
    Location location;
    Action action;
    Storage<PlayerCharacter> players_;

 public:
    ActionSuite() :
        DamageSuite(),
        location(0, "", 0, 5, 5),
        action(AreaFactory::create(1, 1), {
            new DealDamage(new Damage(1, 4, 2), dice),
            new Move(1, 2),
            new Buff({ {"str", -2}, {"dex", -1} }, 2)}, 2) {
        test_enemy_.setStat("str", 10);
        test_enemy_.setStat("dex", 14);

        for (int i = 0; i < 5; ++i) {
            location.npc().add(i, test_enemy_, PositionFactory::create(Tile{1, i}), map);
        }
        location.npc().add(5, test_enemy_, PositionFactory::create(Tile{0, 2}), map);

        EXPECT_CALL(map, currentLocation())
            .WillRepeatedly(ReturnRef(location));

        EXPECT_CALL(map, players())
            .WillRepeatedly(ReturnRef(players_));
    }
};

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

    ASSERT_EQ(error_status, ErrorStatus::Ok);
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
    ASSERT_EQ(error_status, ErrorStatus::Fail);
}

class ActivatableSuite : public ActionSuite {
 protected:
    PlayerCharacter player;
    Action heal_action;

 public:
    ActivatableSuite() :
        ActionSuite(),
        player(8, char_template_, PositionFactory::create(Tile{2, 2}), map, Race(), CharacterClass()),
        heal_action(AreaFactory::create(), { new Heal(3) }, 0, Action::CastType::Self, false) {
            char_template_.setMaxHP(10);
            player.resetHP();
            player.takeDamage(5);

            test_enemy_.setMaxHP(10);
            for (auto& [_, enemy] : location.npc()) {
                enemy.resetHP();
            }
        }
};

TEST_F(ActivatableSuite, PlayerSpellTest) {
    Spell spell(0, "", 0, {action, heal_action}, 5, "int", 2);
    player.spells().add(&spell);

    auto result_buff = Buff({ {"str", -2}, {"dex", -1} }, 2);

    // Let player roll 20 to hit both enemies
    MockDice player_die;
    EXPECT_CALL(player_die, roll(20))
        .WillOnce(Return(20));

    auto player_use_spell = [&] {
        return player.useActivatable("spell", 0, player_die,
                              { Tile{4, 1}, player.mapPosition().first });
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

    ASSERT_EQ(error_status, ErrorStatus::Ok);
    ASSERT_EQ(player.actionPoints(), 5);
    ASSERT_EQ(player.spellPoints(), 3);
    ASSERT_EQ(results, expected_results);

    player.setActionPoints(4);
    std::tie(results, error_status) = player_use_spell();
    ASSERT_EQ(error_status, ErrorStatus::Fail);

    player.setActionPoints(6);
    player.setSpellPoints(1);
    std::tie(results, error_status) = player_use_spell();
    ASSERT_EQ(error_status, ErrorStatus::Fail);
}

#include <gmock/gmock.h>

#include "Activatable.hpp"
#include "Damage.hpp"
#include "CharacterInstance.hpp"
#include "Armor.hpp"
#include "GameState.hpp"

using ::testing::Return;
using ::testing::_;

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
    MOCK_METHOD(void, removeLocation, (), (override));
    MOCK_METHOD(void, switchLocation, (size_t), (override));
    MOCK_METHOD(void, switchLocation, (size_t, size_t), (override));
    MOCK_METHOD(Location&, currentLocation, (), (override));
    MOCK_METHOD(size_t, currentLocationId, (), (const, override));
    MOCK_METHOD(const Location&, getLocation, (size_t), (const, override));  // cppcheck-suppress syntaxError
};

class MockDice : public DiceInterface {
 public:
    MOCK_METHOD(uint8_t, roll, (uint8_t), (const, override));
    MOCK_METHOD(std::vector<uint8_t>, roll, (uint8_t, size_t), (const, override));
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
        character(char_template_, PositionFactory::create(Tile{1, 1}), map),
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
        .WillOnce(Return(6));

    DealDamage damage_resist(new Damage(0, 6, 2), dice);
    damage_resist.updateActionResult(character, &new_result);
    ASSERT_EQ(result.hp - 6, new_result.hp);
}

TEST_F(DamageSuite, DealDamageConsidersVulnerabilities) {
    EXPECT_CALL(*dice, roll(_))
        .WillOnce(Return(3));
    
    DealDamage damage(new Damage(1, 6, 2), dice);
    damage.updateActionResult(character, &new_result);
    ASSERT_EQ(result.hp - 12, new_result.hp);
}

TEST(DiceSuite, ThrowsOnInvalidDice) {
    ASSERT_FALSE(Dice().isValid(-3));
    ASSERT_THROW(DealDamage(new Damage(0, 7, 2), new Dice()), InvalidDice);
    ASSERT_THROW(DealDamage(new Damage(0, -1, 2), new Dice()), InvalidDice);
}

class ActionSuite : public EffectSuite{
 private:
    Character test_enemy_;

 protected:
    std::vector<CharacterInstance> enemies_;

 public:
    ActionSuite() :
        EffectSuite(),
        enemies_() {
        enemies_.reserve(5);
        for (size_t i = 0; i < 5; ++i) {
            enemies_.emplace_back(test_enemy_,
                PositionFactory::create(Tile{0, static_cast<int>(i)}), map);
        }
    }
};

TEST_F(ActionSuite, DISABLED_ActionTest) {
    Action action(AreaFactory::create(1, 1), 3, Action::CastType::Tile,
        {new DealDamage(new Damage(1, 4, 2), new MockDice()),
         new Move(1, 2)});

    // ASSERT_EQ(action.getResults(character_, {0, 1}),
    //           Action::Result{});
}

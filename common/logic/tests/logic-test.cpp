#include <gmock/gmock.h>

#include "Activatable.hpp"
#include "Damage.hpp"
#include "CharacterInstance.hpp"
#include "Armor.hpp"
#include "GameState.hpp"

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
};


TEST_F(AreaSuite, RectAreaWorks) {
    RectangularArea area(1, 2);
    area.setTarget(target_);

    ASSERT_TRUE(area.isInArea(target_));
    ASSERT_TRUE(area.isInArea(target_ + Tile{1, 1}));
    ASSERT_TRUE(area.isInArea(target_ - Tile{1, 2}));

    ASSERT_FALSE(area.isInArea(target_ + Tile{2, 2}));
    ASSERT_FALSE(area.isInArea(target_ - Tile{1, 3}));
};

TEST_F(AreaSuite, CustomAreaWorks) {
    std::vector<Tile> tiles = {Tile{1, 2}, Tile{-1, 3}, Tile{4, 0}};
    CustomArea area(tiles);

    area.setTarget(target_);

    for (const auto& tile : tiles) {
        ASSERT_TRUE(area.isInArea(target_ + tile));
    }

    ASSERT_FALSE(area.isInArea(target_ + Tile{1, 3}));
    ASSERT_FALSE(area.isInArea(target_ - Tile{1, 0}));
};

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
};

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
};

class MockGameMap : public GameMap {
 public:
    MockGameMap() = default;

    MOCK_METHOD(void, addLocation, (size_t, const Location&));
    MOCK_METHOD(void, removeLocation, ());
    MOCK_METHOD(void, switchLocation, (size_t));
    MOCK_METHOD(void, switchLocation, (size_t, size_t));
    MOCK_METHOD(Location&, currentLocation, ());
    MOCK_METHOD(size_t, currentLocationId, (), (const));
    MOCK_METHOD(const Location&, getLocation, (size_t), (const));
};

class FakeDice : public DiceInterface {
    uint8_t roll(uint8_t die) override {
        return die;
    }

    std::vector<uint8_t> roll(uint8_t die, size_t num) override {
        return std::vector<uint8_t>(num, die);
    }
};

class EffectSuite : public ::testing::Test {
 private:
    Character char_template_;
    MockGameMap map_;

 protected:
    CharacterInstance character_;

 public:
    EffectSuite() : character_(char_template_, PositionFactory::createPosition(Tile{1, 1}), map_) {
        char_template_.addResistance(0);
        char_template_.addVulnerability(1);
    }
};

TEST_F(EffectSuite, HealReturnsValidResult) {
    Heal heal(5);
    Effect::Result expected_result(5);
    ASSERT_EQ(heal.getResult(character_), expected_result);
};

TEST_F(EffectSuite, MoveReturnsValidResult) {
    Move move(1, 3);
    Effect::Result expected_result(1, 3);
    ASSERT_EQ(move.getResult(character_), expected_result);
};

TEST_F(EffectSuite, DealDamageReturnsValidResult) {
    DealDamage damage(new Damage(1, 6, 2), new FakeDice());
    Effect::Result expected_result(24);
    ASSERT_EQ(damage.getResult(character_), expected_result);


    DealDamage damage_resist(new Damage(0, 6, 2), new FakeDice());
    Effect::Result expected_result_resist(6);
    ASSERT_EQ(damage_resist.getResult(character_), expected_result_resist);

    ASSERT_THROW(DealDamage(new Damage(0, 7, 2), new FakeDice()), std::exception);
};

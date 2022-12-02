#include <gmock/gmock.h>

#include "Area.hpp"
#include "Position.hpp"

namespace DnD {
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
    std::vector<Offset> offsets = {{1, 2}, {-1, 3}, {4, 0}};
    CustomArea area(offsets);

    area.setTarget(target_);

    for (const auto& offset : offsets) {
        ASSERT_TRUE(area.isInArea(target_ + offset));
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
}  // namespace DnD

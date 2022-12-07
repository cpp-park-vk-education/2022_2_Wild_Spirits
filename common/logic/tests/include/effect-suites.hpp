#pragma once

#include <gmock/gmock.h>

#include "mocks.hpp"

namespace DnD {
class EffectSuite : public ::testing::Test {
 protected:
    Character char_template_;
    MockGameMap map;
    std::unique_ptr<CharacterInstance> character;
    Action::Result result;
    Action::Result new_result;

 public:
    EffectSuite() :
        character(),
        result(0), new_result(result)
    {
        EXPECT_CALL(map, currentLocationId())
            .WillRepeatedly(::testing::Return(0));

        character = std::make_unique<CharacterInstance>(7, char_template_,
                                        PositionFactory::create(Tile{1, 2}), map);

        char_template_.addResistance(0);
        char_template_.addVulnerability(1);
    }
};

class DamageSuite : public EffectSuite {
 protected:
    std::unique_ptr<MockDice> dice;

 public:
    DamageSuite() : dice(std::make_unique<MockDice>()) {}
};
}  // namespace DnD

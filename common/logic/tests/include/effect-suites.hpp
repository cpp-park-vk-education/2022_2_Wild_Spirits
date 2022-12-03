#pragma once

#include <gmock/gmock.h>

#include "mocks.hpp"

namespace DnD {
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

class DamageSuite : public EffectSuite {
 protected:
    std::unique_ptr<MockDice> dice;

 public:
    DamageSuite() : dice(std::make_unique<MockDice>()) {}
};
}  // namespace DnD

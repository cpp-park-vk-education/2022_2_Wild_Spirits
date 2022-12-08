#pragma once

#include <gmock/gmock.h>

#include "mocks.hpp"

namespace DnD {
class EffectSuite : public ::testing::Test {
 protected:
    Character char_template_;
    Storage<CharacterInstance*> all_characters;
    MockGameMap map;
    std::unique_ptr<CharacterInstance> character;
    Action::Result result;
    Action::Result new_result;

 public:
    EffectSuite() :
        character(),
        result(0), new_result(result)
    {
        using ::testing::Return;
        using ::testing::ReturnRef;

        EXPECT_CALL(map, currentLocationId())
            .WillRepeatedly(Return(0));
        
        EXPECT_CALL(map, allCharacters())
            .WillRepeatedly(ReturnRef(all_characters));

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

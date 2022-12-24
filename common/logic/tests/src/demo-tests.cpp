#include <gmock/gmock.h>

#include "Demo.hpp"
#include <memory>

namespace DnD {
using ::testing::SizeIs;

TEST(DemoSuite, ItWorks) {
    std::unique_ptr<LogicProcessor> game;
    std::unique_ptr<GameMap> map;

    ASSERT_NO_THROW({
        game =  std::make_unique<DemoLogicProcessor>();
        map = std::make_unique<DemoGameMap>(*game);
    });

    ASSERT_THAT(map->allCharacters(), SizeIs(4));
    ASSERT_THAT(map->players(), SizeIs(2));
    ASSERT_THAT(map->locations(), SizeIs(2));

    ASSERT_THAT(map->locations().get(0).npc(), SizeIs(2));
    ASSERT_THAT(map->locations().get(1).npc(), SizeIs(0));

    ASSERT_THAT(game->spells(), SizeIs(1));
    ASSERT_THAT(game->races(), SizeIs(2));
    ASSERT_THAT(game->classes(), SizeIs(2));
}

}  // namespace DnD


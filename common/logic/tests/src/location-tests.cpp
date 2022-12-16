#include <gmock/gmock.h>

#include "GameState.hpp"
#include "GameMap.hpp"
#include "OnLocation.hpp"
#include "Storage.hpp"
#include "PlayerCharacter.hpp"

namespace DnD {
class LocationSuite : public ::testing::Test {
 protected:
    GameStateImpl game;
    GameMapImpl map;

    ErrorStatus createDefaultPlayer(size_t id, std::unique_ptr<Position>&& pos) {
        return map.createPlayer(std::make_shared<PlayerCharacter>(id, Character(), std::move(pos), map,
                                std::make_shared<Class>(), std::make_shared<Race>()));
    }

 public:
    LocationSuite() : game(), map(game) {
        map.locations().add(0, "", 0, 5, 5);
        map.locations().add(1, "", 0, 4, 4);
    }
};

TEST_F(LocationSuite, /*DISABLED_*/CharactersAreCreated) {  // cppcheck-suppress [syntaxError]
    auto status = createDefaultPlayer(0, PositionFactory::create(Tile{1, 1}));
    ASSERT_EQ(status, ErrorStatus::OK);

    // status = createDefaultPlayer(0, PositionFactory::create(Tile{1, 2}));
    // ASSERT_EQ(status, ErrorStatus::ALREADY_EXISTS);

    // status = createDefaultPlayer(1, PositionFactory::create(Tile{1, 1}));
    // ASSERT_EQ(status, ErrorStatus::TILE_OCCUPIED);
}
}  // namespace DnD

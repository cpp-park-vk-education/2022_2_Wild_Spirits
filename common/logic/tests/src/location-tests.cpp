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
    std::shared_ptr<NPC> enemy;

    ErrorStatus createDefaultPlayer(size_t id, std::unique_ptr<Position>&& pos) {
        return map.createPlayer(std::make_shared<PlayerCharacter>(id, Character(), std::move(pos), map,
                                std::make_shared<Class>(), std::make_shared<Race>()));
    }

    std::vector<Tile> expectedFree(const Location& location, const std::vector<Tile>& occupied) {
        std::vector<Tile> expected_free_tiles;
        expected_free_tiles.reserve(location.width() * location.height() - occupied.size());

        for (size_t x = 0; x < location.width(); ++x) {
            for (size_t y = 0; y < location.height(); ++y) {
                Tile tile{x, y};
                if (std::find(occupied.begin(), occupied.end(), tile) == occupied.end()) {
                    expected_free_tiles.push_back(tile);
                }
            }
        }

        return expected_free_tiles;
    }

 public:
    LocationSuite() : game(), map(game), enemy(std::make_shared<NPC>()) {
        map.locations().add(0, "", 0, 5, 5);
        map.locations().add(1, "", 0, 4, 4);
    }
};

std::ostream& operator<<(std::ostream& out, const Tile& tile) {
    return out << '{' << tile.x << ", " << tile.y << '}';
}

TEST_F(LocationSuite, CharactersAreCreated) {  // cppcheck-suppress [syntaxError]
    auto status = createDefaultPlayer(0, PositionFactory::create(Tile{1, 1}));
    ASSERT_EQ(status, ErrorStatus::OK);

    status = createDefaultPlayer(0, PositionFactory::create(Tile{1, 2}));
    ASSERT_EQ(status, ErrorStatus::ALREADY_EXISTS);

    status = createDefaultPlayer(1, PositionFactory::create(Tile{1, 1}));
    ASSERT_EQ(status, ErrorStatus::TILE_OCCUPIED);

    status = createDefaultPlayer(1, PositionFactory::create(Tile{0, 0}, Tile{2, 2}));
    ASSERT_EQ(status, ErrorStatus::TILE_OCCUPIED);

    status = createDefaultPlayer(1, PositionFactory::create(Tile{5, 5}));
    ASSERT_EQ(status, ErrorStatus::OUT_OF_LOCATION_BOUNDS);

    auto& location = map.locations().get(0);
    status = location.createNPC(1, enemy, PositionFactory::create(Tile{0, 0}, Tile{0, 2}), map);
    ASSERT_EQ(status, ErrorStatus::OK);

    status = location.createNPC(2, enemy, PositionFactory::create(Tile{0, 1}), map);
    ASSERT_EQ(status, ErrorStatus::TILE_OCCUPIED);

    std::vector<Tile> occupied_tiles = {
        Tile{0, 0}, Tile{0, 1}, Tile{0, 2}, Tile{1, 1}
    };

    ASSERT_EQ(location.freeTiles(), expectedFree(location, occupied_tiles));
}

TEST_F(LocationSuite, ResizeTest) {
    auto& location = map.locations().get(0);

    auto status = location.createNPC(2, enemy, PositionFactory::create(Tile{2, 4}), map);
    ASSERT_EQ(status, ErrorStatus::OK);

    status = createDefaultPlayer(0, PositionFactory::create(Tile{1, 3}, Tile{2, 3}));
    ASSERT_EQ(status, ErrorStatus::OK);

    std::vector<Tile> occupied_tiles = {
        Tile{2, 4}, Tile{1, 3}, Tile{2, 3}
    };

    ASSERT_EQ(location.freeTiles(), expectedFree(location, occupied_tiles));

    status = location.setHeight(6);
    ASSERT_EQ(status, ErrorStatus::OK);

    status = location.setWidth(6);
    ASSERT_EQ(status, ErrorStatus::OK);

    status = location.setSize(5, 5);
    ASSERT_EQ(status, ErrorStatus::OK);

    ASSERT_EQ(location.freeTiles(), expectedFree(location, occupied_tiles));

    status = location.setWidth(4);
    ASSERT_EQ(status, ErrorStatus::OK);

    status = location.setWidth(2);
    ASSERT_EQ(status, ErrorStatus::WOULD_ERASE_CHARACTERS);

    status = location.setHeight(4);
    ASSERT_EQ(status, ErrorStatus::WOULD_ERASE_CHARACTERS);

    status = location.setSize(5, 4);
    ASSERT_EQ(status, ErrorStatus::WOULD_ERASE_CHARACTERS);

    ASSERT_EQ(location.freeTiles(), expectedFree(location, occupied_tiles));
}
}  // namespace DnD

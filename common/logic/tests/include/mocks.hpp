#include <gmock/gmock.h>

#include "GameMap.hpp"
#include "Dice.hpp"

namespace DnD {
class MockGameMap : public GameMap {
 public:
    MockGameMap() = default;
    MOCK_METHOD(Storage<Location>&, locations, (), (override));
    MOCK_METHOD(ErrorStatus, switchLocation, (size_t), (override));
    MOCK_METHOD(ErrorStatus, switchLocation, (size_t, size_t), (override));
    MOCK_METHOD(Location&, currentLocation, (), (override));
    MOCK_METHOD(size_t, currentLocationId, (), (const, override));
    MOCK_METHOD(Storage<PlayerCharacter>&, players, (), (const, override));
    MOCK_METHOD(Storage<CharacterInstance*>&, allCharacters, (), (const, override));
};

class MockDice : public DiceInterface {
 public:
    MOCK_METHOD(uint8_t, roll, (uint8_t), (const, override));
    MOCK_METHOD(std::vector<uint8_t>, roll, (uint8_t, size_t), (const, override));
    std::unique_ptr<DiceInterface> clone() const override {
        return std::make_unique<MockDice>();
    }
};
}  // namespace DnD

#include <gmock/gmock.h>

#include "GameMap.hpp"
#include "Dice.hpp"

class MockGameMap : public GameMap {
 public:
    MockGameMap() = default;
    MOCK_METHOD(Storage<Location>&, locations, (), (override));
    MOCK_METHOD(void, switchLocation, (size_t), (override));
    MOCK_METHOD(void, switchLocation, (size_t, size_t), (override));
    MOCK_METHOD(Location&, currentLocation, (), (override));
    MOCK_METHOD(size_t, currentLocationId, (), (const, override));
    MOCK_METHOD(Storage<PlayerCharacter>&, players, ());
};

class MockDice : public DiceInterface {
 public:
    MOCK_METHOD(uint8_t, roll, (uint8_t), (const, override));
    MOCK_METHOD(std::vector<uint8_t>, roll, (uint8_t, size_t), (const, override));
    DiceInterface* clone() const override {
        return new MockDice();
    }
};

#pragma once

#include <vector>
#include <cstdlib>
#include <cstdint>

class DiceInterface {
 public:
    virtual uint8_t roll(uint8_t die) = 0;
    virtual std::vector<uint8_t> roll(uint8_t die, size_t num) = 0;

    virtual ~DiceInterface() {}
};

class Dice : public DiceInterface {
 public:
    uint8_t roll(uint8_t die) override {
        return 0;
    }

    std::vector<uint8_t> roll(uint8_t die, size_t num) override {
        return std::vector<uint8_t>(num);
    }
};

#pragma once

#include <vector>
#include <cstdlib>
#include <cstdint>

class Dice {
 public:
    static uint8_t roll(uint8_t die) {
        return 0;
    }

    static std::vector<uint8_t> roll(uint8_t die, size_t num) {
        return std::vector<uint8_t>(num);
    }
};

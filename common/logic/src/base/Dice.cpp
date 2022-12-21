#include "Dice.hpp"

#include <algorithm>
#include <iostream>

namespace DnD {
    const std::set<uint8_t> DiceInterface::valid_dice_ = {4, 6, 8, 10, 12, 20};

    std::mt19937 Dice::gen_(std::random_device{}());  // NOLINT

    uint16_t Dice::roll(uint8_t die) const {
        std::uniform_int_distribution<uint16_t> dist(1, die);
        auto res = dist(gen_);
        return res;
    }

    std::unique_ptr<DiceInterface> Dice::clone() const {
        return std::make_unique<Dice>();
    }

    std::vector<uint16_t> Dice::roll(uint8_t die, size_t num) const {
        std::uniform_int_distribution<uint16_t> dist(1, die);
        std::vector<uint16_t> res(num);
        std::generate_n(res.begin(), num, [&dist] { return dist(gen_); });
        return res;
    }
};  // namespace DnD

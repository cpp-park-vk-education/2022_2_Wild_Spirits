#include "Dice.hpp"

namespace DnD {
    const std::set<uint8_t> DiceInterface::valid_dice_ = {4, 6, 8, 10, 12, 20};

    uint8_t Dice::roll(uint8_t die) const {
        return 0;
    }

    std::unique_ptr<DiceInterface> Dice::clone() const {
        return std::make_unique<Dice>();
    }

    std::vector<uint8_t> Dice::roll(uint8_t die, size_t num) const {
        return std::vector<uint8_t>(num);
    }
};  // namespace DnD

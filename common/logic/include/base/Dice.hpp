#pragma once

#include <vector>
#include <memory>
#include <set>
#include <random>

#include <cstddef>
#include <cstdint>

namespace DnD {
class DiceInterface {
 private:
    static const std::set<uint8_t> valid_dice_;
    
 public:
    virtual uint8_t roll(uint8_t die) const = 0;
    virtual std::vector<uint8_t> roll(uint8_t die, size_t num) const = 0;

    virtual bool isValid(uint8_t die) const {
        return valid_dice_.contains(die);
    }

    virtual std::unique_ptr<DiceInterface> clone() const = 0;
    virtual ~DiceInterface() {}
};

class Dice : public DiceInterface {
 private:
    static std::mt19937 gen_;

 public:
    static constexpr uint8_t D20 = 20;

    uint8_t roll(uint8_t die) const override;
    std::unique_ptr<DiceInterface> clone() const override;
    std::vector<uint8_t> roll(uint8_t die, size_t num) const override;
};
}  // namespace DnD

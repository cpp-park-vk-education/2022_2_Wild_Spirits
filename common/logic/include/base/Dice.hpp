#pragma once

#include <vector>
#include <set>
#include <cstdlib>
#include <cstdint>

class DiceInterface {
 protected:
    static const inline std::set<uint8_t> valid_dice_ = {4, 6, 8, 10, 12, 20};
    
 public:
    virtual uint8_t roll(uint8_t die) const = 0;
    virtual std::vector<uint8_t> roll(uint8_t die, size_t num) const = 0;

    virtual bool isValid(uint8_t die) const {
        return valid_dice_.contains(die);
    }

    virtual DiceInterface* clone() const = 0;
    virtual ~DiceInterface() {}
};

class Dice : public DiceInterface {
 public:
    uint8_t roll(uint8_t die) const override {
        return 0;
    }

    DiceInterface* clone() const override {
        return new Dice();
    }

    bool isValid(uint8_t die) const override {
        return valid_dice_.contains(die);
    }

    std::vector<uint8_t> roll(uint8_t die, size_t num) const override {
        return std::vector<uint8_t>(num);
    }
};

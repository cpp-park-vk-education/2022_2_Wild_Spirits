#pragma once

#include "Effect.hpp"
#include "Exception.hpp"
#include "Dice.hpp"

#include <exception>

namespace DnD {
class DealDamage : public Effect {
 private:
    uint8_t damage_type_;
    uint8_t die_type_;
    size_t times_;

    DiceInterface* dice_;
 
 public:
    DealDamage(uint8_t dmg_type, uint8_t die_type, size_t times, DiceInterface* dice) :
        damage_type_(dmg_type), die_type_(die_type), times_(times), dice_(dice) {}

    DealDamage(const DealDamage& other) :
        DealDamage(other.damage_type_, other.die_type_, other.times_, other.dice_->clone()) {}

    Effect* clone() const override {
        return new DealDamage(*this);
    }

    std::string info() const override {
        return "";
    }

    void updateActionResult(const CharacterInstance& character, Action::Result* result) const override;

    ~DealDamage() override {
        delete dice_;
    }
};

class InvalidDice : public Exception {
 public:
    InvalidDice(int8_t die) : Exception(("Die " + std::to_string(die) + " is not allowed").c_str()) {}
};
}  // namespace DnD

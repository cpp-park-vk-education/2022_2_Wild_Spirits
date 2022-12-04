#pragma once

#include "Effect.hpp"
#include "Exception.hpp"
#include "Dice.hpp"

#include <exception>
#include <memory>

#include "DamageType.hpp"

namespace DnD {
class DealDamage : public Effect {
 private:
    DamageType damage_type_;
    uint8_t die_type_;
    size_t times_;

    std::unique_ptr<DiceInterface> dice_;
 
 public:
    DealDamage(const DamageType& dmg_type, uint8_t die_type, size_t times, std::unique_ptr<DiceInterface>&& dice) :
        damage_type_(dmg_type), die_type_(die_type), times_(times), dice_(std::move(dice)) {}

    DealDamage(const DealDamage& other) :
        DealDamage(other.damage_type_, other.die_type_, other.times_, other.dice_->clone()) {}

    std::unique_ptr<Effect> clone() const override {
        return std::make_unique<DealDamage>(*this);
    }

    std::string info() const override {
        return "Deal " + std::to_string(times_) + " * d" +
                std::to_string(die_type_) + " in " + damage_type_.name();
    }

    void updateActionResult(const CharacterInstance& character, Action::Result* result) const override;
};

class InvalidDice : public Exception {
 public:
    InvalidDice(int8_t die) : Exception(("Die " + std::to_string(die) + " is not allowed").c_str()) {}
};
}  // namespace DnD

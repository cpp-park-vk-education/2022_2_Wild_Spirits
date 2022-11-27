#pragma once

#include "Effect.hpp"
#include "Exception.hpp"
#include "Dice.hpp"

#include <exception>

struct DamageClass {
    uint8_t damage_type;
    uint8_t die_type;
    size_t times;
};

class DamageInterface {
 public:
    virtual size_t calculateDamageTo(const CharacterInstance&, const DiceInterface&) const = 0;

    virtual DamageInterface* clone() const = 0;

    virtual ~DamageInterface() {}
};

class Damage : public DamageInterface {
 private:
    DamageClass damage_;

 public:
    Damage(uint8_t damage_type, uint8_t die_type, size_t times)
        : damage_{damage_type, die_type, times} {}

    DamageInterface* clone() const override {
        return new Damage(damage_.damage_type, damage_.die_type, damage_.times);
    }

    size_t calculateDamageTo(const CharacterInstance&, const DiceInterface&) const override {
        return 0;
    }
};

class DealDamage : public Effect {
 private:
    DamageInterface* damage_;
    DiceInterface* dice_;
 
 public:
    DealDamage(DamageInterface* damage, DiceInterface* dice) : damage_(damage), dice_(dice) {}

    DealDamage(const DealDamage& other) : DealDamage(other.damage_->clone(), other.dice_->clone()) {}

    Effect* clone() const override {
        return new DealDamage(*this);
    }

    void updateActionResult(const CharacterInstance& character, Action::Result* result) const override {}

    ~DealDamage() override {
        delete damage_;
        delete dice_;
    }
};

class InvalidDice : public DnD_Exception {
 public:
    InvalidDice(int8_t die) : DnD_Exception(("Die " + std::to_string(die) + " is not allowed").c_str()) {}
};

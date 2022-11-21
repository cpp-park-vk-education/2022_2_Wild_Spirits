#pragma once

#include "Effect.hpp"
#include "Dice.hpp"

struct DamageClass {
    uint8_t damage_type;
    uint8_t die_type;
    size_t times;
};

class DamageInterface {
 public:
    virtual size_t calculateDamageTo(const CharacterInstance&, const DiceInterface&) const = 0;
    virtual ~DamageInterface() {}
};

class Damage : public DamageInterface {
 private:
    DamageClass damage_;

 public:
    Damage(uint8_t damage_type, uint8_t die_type, size_t times)
        : damage_{damage_type, die_type, times} {}

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

    Result getResult(const CharacterInstance& character) const override {
        return Result{};
    }

    ~DealDamage() override {
        delete damage_;
        delete dice_;
    }
};

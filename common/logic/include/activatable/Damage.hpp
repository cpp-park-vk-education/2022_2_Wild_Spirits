#pragma once

#include "Effect.hpp"

struct DamageClass {
    uint8_t damage_type;
    uint8_t die_type;
    size_t times;
};

class DamageInterface {
 public:
    virtual size_t calculateDamageTo(const CharacterInstance&) const = 0;
};

class Damage : public DamageInterface {
 private:
    DamageClass damage_;

 public:
    Damage(uint8_t damage_type, uint8_t die_type, size_t times)
        : damage_{damage_type, die_type, times} {}

    size_t calculateDamageTo(const CharacterInstance&) const override {
        return 0;
    }
};

class DealDamage : public Effect {
 private:
    DamageInterface* damage_;
 
 public:
    DealDamage(DamageInterface* damage) : damage_(damage) {}

    Result getResult(const CharacterInstance& character) const override {
        return Result{};
    }

    ~DealDamage() override {
        delete damage_;
    }
};

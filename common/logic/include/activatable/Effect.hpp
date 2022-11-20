#pragma once

// #include "CharacterInstance.hpp"
#include "WithStats.hpp"

class CharacterInstance;

class Effect {
 public:
    struct Result {
        int x;
        int y;
        unsigned int hp;
        WithStats::Stats* buff = nullptr;
    };

    virtual Result getResult(const CharacterInstance& character) const = 0;

    virtual ~Effect() {}
};

class Heal : public Effect {
 private:
    unsigned int amount_;

 public:
    Heal(unsigned int amount) : amount_(amount) {}

    Result getResult(const CharacterInstance& character) const override {
        return Result{};
    }
};

class Move : public Effect {
 private:
    int x_;
    int y_;

 public:
    Move(int x, int y) : x_(x), y_(y) {}

    Result getResult(const CharacterInstance& character) const override {
        return Result{};
    }
};

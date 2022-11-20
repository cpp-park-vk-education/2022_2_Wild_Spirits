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
    Result getResult(const CharacterInstance& character) const override {
        return Result{};
    }
};

class Move : public Effect {
 private:
    int x;
    int y;

 public:
    Result getResult(const CharacterInstance& character) const override {
        return Result{};
    }
};

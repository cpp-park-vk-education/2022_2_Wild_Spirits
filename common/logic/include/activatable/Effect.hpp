#pragma once

#include "Action.hpp"

class CharacterInstance;

class Effect {
 public:
    virtual void updateActionResult(const CharacterInstance& character, Action::Result* result) const = 0;
    virtual ~Effect() {}
};

class Heal : public Effect {
 private:
    unsigned int amount_;

 public:
    Heal(unsigned int amount) : amount_(amount) {}
    void updateActionResult(const CharacterInstance& character, Action::Result* result) const override {}
};

class Move : public Effect {
 private:
    int x_;
    int y_;

 public:
    Move(int x, int y) : x_(x), y_(y) {}
    void updateActionResult(const CharacterInstance& character, Action::Result* result) const override {}
};

#pragma once

#include "Action.hpp"

#include <memory>

namespace DnD {
class CharacterInstance;

class Effect {
 public:
    virtual void updateActionResult(const CharacterInstance& character, Action::Result* result) const = 0;
    virtual std::string info() const = 0;
    virtual std::unique_ptr<Effect> clone() const = 0;
    virtual ~Effect() {}
};

class Heal : public Effect {
 private:
    unsigned int amount_;

 public:
    Heal(unsigned int amount) : amount_(amount) {}

    std::string info() const override {
        return "Heal target by " + std::to_string(amount_) + " hp";
    }

    std::unique_ptr<Effect> clone() const override {
        return std::make_unique<Heal>(amount_);
    }

    void updateActionResult(const CharacterInstance& character, Action::Result* result) const override;
};

class Move : public Effect {
 private:
    Offset offset_;

 public:
    Move(long long x, long long y) : offset_{x, y} {}

    std::string info() const override {
        return "Move target by " + std::to_string(offset_.x) + " horizontally and " +
                std::to_string(offset_.y) + "vertically, depending on character's relative positions";
    }

    std::unique_ptr<Effect> clone() const override {
        return std::make_unique<Move>(*this);
    }

    void updateActionResult(const CharacterInstance& character, Action::Result* result) const override;
};
}  // namespace DnD

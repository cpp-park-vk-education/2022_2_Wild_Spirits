#pragma once

namespace DnD {
class TurnBased {
 public:
    virtual void onTurnStart() = 0;
};

class Temporal : public TurnBased {
 private:
    unsigned int turns_;

 public:
    explicit Temporal(unsigned int turns = 0) : turns_(turns) {}

    unsigned int turnsLeft() const {
        return turns_;
    }

    void reset(unsigned int turns) {
        turns_ = turns;
    }

    void onTurnStart() override {
        if (turns_) {
            --turns_;
        }
    }
};
}  // namespace DnD
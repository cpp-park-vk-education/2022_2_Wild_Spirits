#pragma once
#include <concepts>

namespace DnD {

class TurnStateChange {
 protected:
    virtual void turnStateChangeAction() {}
};

class TurnStart : public TurnStateChange {
 public:
    virtual void onTurnStart() {
        turnStateChangeAction();
    }
};

class TurnEnd : public TurnStateChange {
 public:
    virtual void onTurnEnd() {
        turnStateChangeAction();
    }
};

class TurnBased : public TurnStart, public TurnEnd {};

template <std::derived_from<TurnStateChange> T>
class Temporal : public T {
 private:
    unsigned int turns_;
 
 protected:
    void reset(unsigned int turns) {
        turns_ = turns;
    }

 public:
    explicit Temporal(unsigned int turns = 0) : turns_(turns) {}

    unsigned int turnsLeft() const {
        return turns_;
    }

    void turnStateChangeAction() override {
        if (turns_) {
            --turns_;
        }
    }
};
}  // namespace DnD
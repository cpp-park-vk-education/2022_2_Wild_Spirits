#include "Action.hpp"

#include "Effect.hpp"

Action::Action(Area* area, unsigned int range, CastType cast_type, std::vector<Effect*> effects) :
    cast_type_(cast_type), area_(area), range_(range), effects_(effects) {}

void Action::setCastType(CastType cast_type) {
    cast_type_ = cast_type;
}

Action::CastType Action::castType() {
    return cast_type_;
}

void Action::setArea(Area* area) {
    delete area_;
    area_ = area;
}

const std::vector<Effect*>& Action::effects() const {
    return effects_;
}

void Action::addEffect(Effect* effect) {
    effects_.push_back(effect);
}

void Action::removeEffect(size_t effect_id) {
    effects_.erase(effects_.begin() + effect_id);
}

std::vector<Action::Result> Action::getResults(const CharacterInstance&, const Tile& tile) {
    return {};
}

Action::~Action() {
    delete area_;
    for (auto effect : effects_) {
        delete effect;
    }
}

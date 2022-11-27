#include "Action.hpp"

#include "Effect.hpp"

Action::Action(Area* area, unsigned int range, std::vector<Effect*> effects,
               CastType cast_type, bool can_miss, const std::string& target_scaling) :
    cast_type_(cast_type), area_(area),
    range_(range), effects_(effects),
    can_miss_(can_miss), target_scaling_(target_scaling) {}

void Action::setCastType(CastType cast_type) {
    cast_type_ = cast_type;
}

Action::CastType Action::castType() const {
    return cast_type_;
}

void Action::setTargetScaling(const std::string& scaling) {
    target_scaling_ = scaling;
}

const std::string& Action::targetScaling() const {
    return target_scaling_;
}

bool Action::canMiss() const {
    return can_miss_;
}

void Action::toggleMissable() {
    can_miss_ = (can_miss_ + 1) % 2;
}

void Action::setArea(Area* area) {
    delete area_;
    area_ = area;
}

std::vector<Effect*>& Action::effects() {
    return effects_;
}

void Action::addEffect(Effect* effect) {
    effects_.push_back(effect);
}

void Action::removeEffect(size_t effect_id) {
    effects_.erase(effects_.begin() + effect_id);
}

std::tuple<std::vector<Action::Result>, ErrorStatus> Action::getResults(const CharacterInstance&, const Tile& tile) {
    return {};
}

Action::~Action() {
    delete area_;
    for (auto effect : effects_) {
        delete effect;
    }
}

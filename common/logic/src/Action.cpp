#include "Action.hpp"

#include "Effect.hpp"
#include "Buff.hpp"

#include <utility>

namespace DnD {
Action::Result::Result(size_t char_id) : char_id_(char_id) {}

Action::Result::Result(size_t char_id, Tile pos, int hp, const std::vector<Buff>& buffs) :
    char_id_(char_id),
    pos(pos),
    hp(hp),
    buffs(buffs) {}

Action::Result::~Result() {}

Action::Action(Area* area, const std::vector<Effect*>& effects, unsigned int range,
               CastType cast_type, bool can_miss, const std::string& target_scaling) :
    cast_type_(cast_type), area_(area),
    range_(range), effects_(effects),
    can_miss_(can_miss), target_scaling_(target_scaling) {}

Action::Action(const Action& other) :
    cast_type_(other.cast_type_), area_(other.area_->clone()), range_(other.range_),
    effects_(other.effects_.size()), can_miss_(other.can_miss_), target_scaling_(other.target_scaling_) {
        for (size_t i = 0; i < other.effects_.size(); ++i) {
            effects_[i] = other.effects_[0]->clone();
        }
}

Action& Action::operator=(const Action& other) {
    auto tmp = other;
    swap(tmp);
    return *this;
}

Action::Action(Action&& other) :
     cast_type_(other.cast_type_), area_(other.area_), range_(other.range_),
     effects_(std::move(other.effects_)), can_miss_(other.can_miss_),
     target_scaling_(std::move(other.target_scaling_)) {
    other.area_ = nullptr;
    other.range_ = 0;
    other.can_miss_ = true;
    other.target_scaling_ = "dex";
}

Action& Action::operator=(Action&& other) {
    auto tmp = std::move(other);
    swap(tmp);
    return *this;
}

void Action::swap(Action& other) {
    std::swap(area_, other.area_);
    std::swap(effects_, other.effects_);
    std::swap(range_, other.range_);
    std::swap(can_miss_, other.can_miss_);
    std::swap(target_scaling_, other.target_scaling_);
    std::swap(cast_type_, other.cast_type_);
}

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
    if (effect_id > effects_.size()) {
        return;
    }

    auto it = effects_.begin() + effect_id;
    delete *it;
    effects_.erase(it);
}

std::tuple<std::vector<Action::Result>, ErrorStatus> Action::getResults(
        const CharacterInstance&, const Tile& tile, uint8_t dice_roll_res) {
    return {};
}

Action::~Action() {
    delete area_;
    for (auto effect : effects_) {
        delete effect;
    }
}
}  // namespace DnD

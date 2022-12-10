#include "Action.hpp"

#include "Effect.hpp"
#include "Buff.hpp"
#include "Armor.hpp"
#include "GameMap.hpp"

#include "CharacterInstance.hpp"
#include "PlayerCharacter.hpp"
#include "Location.hpp"

#include <utility>
#include <tuple>

namespace DnD {
Action::Result::Result(size_t char_id) : char_id_(char_id) {}

Action::Result::Result(size_t char_id, Tile pos, int hp, const std::list<Buff>& buffs) :
    char_id_(char_id),
    pos(pos),
    hp(hp),
    buffs(buffs) {}

bool Action::Result::operator==(const Result& other) const {
    return std::tie(char_id_, pos, hp, buffs) == std::tie(other.char_id_, other.pos, other.hp, other.buffs);
}

Action::Result& Action::Result::operator+=(Result&& other) {
    if (char_id_ != other.char_id_) {
        return *this;
    }

    pos += other.pos;
    hp += other.hp;

    buffs.splice(buffs.end(), other.buffs);
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Action::Result& result) {
    out << "{ Id: " << result.char_id_ << ", Pos: {" << result.pos.x << ", " << result.pos.y
               << "}, Health: " << result.hp << ", Buffs: { ";
    for (auto& buff : result.buffs) {
        out << buff;
    }
    return out << "} }";
}

Action::Action(Action::AreaPtr&& area, std::vector<Action::EffectPtr>&& effects, Target target_type,
               unsigned int range, Cast cast_type, bool can_miss, const std::string& target_scaling) :
    cast_type_(cast_type), target_type_(target_type), area_(std::move(area)),
    range_(range), effects_(std::move(effects)),
    can_miss_(can_miss), target_scaling_(target_scaling) {}

Action::Action(const Action& other) :
    cast_type_(other.cast_type_), target_type_(other.target_type_),
    area_(other.area_->clone()), range_(other.range_),
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
     cast_type_(other.cast_type_), target_type_(other.target_type_),
     area_(std::move(other.area_)), range_(other.range_),
     effects_(std::move(other.effects_)), can_miss_(other.can_miss_),
     target_scaling_(std::move(other.target_scaling_)) {
    other.range_ = 0;
    other.can_miss_ = true;
    other.target_scaling_ = Armor::kScaling;
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
    std::swap(target_type_, other.target_type_);
}

void Action::setCastType(Cast cast_type) {
    cast_type_ = cast_type;
}

Action::Cast Action::castType() const {
    return cast_type_;
}

void Action::setTargetType(Target target_type) {
    target_type_ = target_type;
}

Action::Target Action::targetType() const {
    return target_type_;
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
    can_miss_ = !can_miss_;
}

void Action::setArea(Action::AreaPtr&& area) {
    area_ = std::move(area);
}

const Action::AreaPtr& Action::area() const {
    return area_;
}

std::vector<Action::EffectPtr>& Action::effects() {
    return effects_;
}

void Action::addEffect(Action::EffectPtr&& effect) {
    effects_.push_back(std::move(effect));
}

void Action::removeEffect(size_t effect_id) {
    if (effect_id > effects_.size()) {
        return;
    }

    effects_.erase(effects_.begin() + effect_id);
}

template <typename T>
void Action::applyEffectsTo(Storage<T>& characters, std::vector<Action::Result>* results,
                            uint8_t dice_roll_res, std::function<bool(const CharacterInstance&)> predicate) const {
    for (const auto& [_, character] : characters) {
        if (!predicate(character) || !character.isInArea(*area_)) {
            continue;
        }

        if (can_miss_ && target_scaling_ == Armor::kScaling) {
            if (dice_roll_res < character.armorClass()) {
                continue;
            }
        } else if (can_miss_ && dice_roll_res < character.original().stat(target_scaling_)) {
            continue;
        }

        results->emplace_back(character.id());

        for (auto& effect : effects_) {
            effect->updateActionResult(character, &results->back());
        }
    }
}

std::tuple<std::vector<Action::Result>, ErrorStatus> Action::getResults(
        const CharacterInstance& actor, const Tile& tile, uint8_t dice_roll_res) const {
    std::vector<Action::Result> results;

    if (cast_type_ != Cast::Self && actor.centerPos().distance(tile) > range_) {
        return std::make_tuple(results, ErrorStatus::INVALID_CAST_RANGE);
    }

    area_->setTarget(tile);

    if (target_type_ == Target::Allies || target_type_ == Target::Both) {
        applyEffectsTo(actor.map().players(), &results, dice_roll_res);

        applyEffectsTo(actor.location().npc(), &results, dice_roll_res,
            [] (const auto& character) { return !character.isHostile(); });
    }

    if (target_type_ == Target::Enemies || target_type_ == Target::Both) {
        applyEffectsTo(actor.location().npc(), &results, dice_roll_res,
            [] (const auto& character) { return character.isHostile(); });
    }

    return std::make_tuple(results, ErrorStatus::OK);
}
}  // namespace DnD

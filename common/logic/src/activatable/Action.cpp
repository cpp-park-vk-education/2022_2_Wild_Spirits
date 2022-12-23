#include "Action.hpp"

#include "Effect.hpp"
#include "Dice.hpp"
#include "Buff.hpp"
#include "Armor.hpp"
#include "GameMap.hpp"

#include "CharacterInstance.hpp"
#include "PlayerCharacter.hpp"
#include "Location.hpp"
#include "Print.hpp"

#include <utility>
#include <tuple>

namespace DnD {
Action::Result::Result(size_t char_id) : char_id_(char_id) {}

Action::Result::Result(size_t char_id, Tile pos, int hp, const std::list<Buff>& buffs,
                       const std::vector<Dice::Roll>& roll_res) :
    char_id_(char_id),
    pos(pos),
    hp(hp),
    buffs(buffs),
    roll_results(roll_res) {}

bool Action::Result::operator==(const Result& other) const {
    return std::tie(char_id_, pos, hp, buffs, roll_results) ==
           std::tie(other.char_id_, other.pos, other.hp, other.buffs, other.roll_results);
}

Action::Result& Action::Result::operator+=(Result&& other) {
    if (char_id_ != other.char_id_) {
        return *this;
    }

    pos += other.pos;
    hp += other.hp;

    buffs.splice(buffs.end(), other.buffs);
    std::copy(other.roll_results.begin(), other.roll_results.end(), std::back_inserter(roll_results));
    return *this;
}

std::ostream& operator<<(std::ostream& out, Dice::Roll roll) {
     return out << "{'rolled': " << roll.rolled
                << ", 'got': " << roll.got << '}';
}

std::ostream& operator<<(std::ostream& out, const Action::Result& result) {
    out << "{'id': " << result.char_id_ << ", 'pos': {" << "'x': "
        << result.pos.x << ", 'y': " << result.pos.y
        << "}, 'hp': " << result.hp;

    if (!result.buffs.empty()) {
        out << ", 'buffs': ";
        printIterable(result.buffs.begin(), result.buffs.end(), out);
    }

    if (!result.roll_results.empty()) {
        out << ", 'rolls': ";
        printIterable(result.roll_results.begin(), result.roll_results.end(), out);
    }
    return out << "}";
}

Action::Action(Action::AreaPtr&& area, std::vector<Action::EffectPtr>&& effects, Target target_type,
               unsigned int range, bool can_miss, const std::string& target_scaling) :
    target_type_(target_type), area_(std::move(area)),
    range_(range), effects_(std::move(effects)),
    can_miss_(can_miss), target_scaling_(target_scaling) {}

Action::Action(const Action& other) :
    target_type_(other.target_type_),
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
     target_type_(other.target_type_),
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
    std::swap(target_type_, other.target_type_);
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

void Action::setMissable(bool value) {
    can_miss_ = value;
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
void Action::applyEffectsTo(SharedStorage<T>& characters, std::vector<Action::Result>* results,
                            uint8_t dice_roll_res, std::function<bool(const CharacterInstance&)> predicate) const {
    for (const auto& [_, character] : characters) {
        if (!predicate(*character) || !character->isInArea(*area_)) {
            continue;
        }

        if (can_miss_ && target_scaling_ == Armor::kScaling) {
            if (dice_roll_res < character->armorClass()) {
                continue;
            }
        } else if (can_miss_ && dice_roll_res < character->original().stat(target_scaling_)) {
            continue;
        }

        results->emplace_back(character->id());

        for (auto& effect : effects_) {
            effect->updateActionResult(*character, &results->back());
        }
    }
}

std::tuple<std::vector<Action::Result>, ErrorStatus> Action::getResults(
        const CharacterInstance& actor, const Tile& tile, uint8_t dice_roll_res) const {
    std::vector<Action::Result> results;

    if (actor.centerPos().distance(tile) > range_) {
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

ErrorStatus Action::setCharacteristic(const std::string& which, const SetterParam& to) {
    if (which == "scaling") {
        auto value = std::get_if<std::string>(&to);
        if (!value) {
            return ErrorStatus::INVALID_ARGUMENT;
        }
        setTargetScaling(*value);
        return ErrorStatus::OK;
    }

    auto value = std::get_if<int64_t>(&to);
    if (!value) {
        return ErrorStatus::INVALID_ARGUMENT;
    }

    if (which == "miss") {
        setMissable(*value);
        return ErrorStatus::OK;
    } else if (which == "target") {
        setTargetType(static_cast<Target>(*value));
        return ErrorStatus::OK;
    }

    return ErrorStatus::INVALID_SETTER;
}
}  // namespace DnD
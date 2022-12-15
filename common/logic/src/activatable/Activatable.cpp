#include "Activatable.hpp"

#include "CharacterInstance.hpp"
#include "GameMap.hpp"

#include <algorithm>
#include <iterator>

namespace DnD {
ActivatableInterface::Result::Result(size_t id, uint8_t dice_roll, int ap, unsigned int resource,
                                     const std::vector<Action::Result>& input_results) :
    char_id(id), dice_roll_res(dice_roll), action_points(ap), resource_spent(resource),
    results(input_results.begin(), input_results.end()) {}

bool ActivatableInterface::Result::operator==(const Result& other) const {
    return std::tie(char_id, dice_roll_res, action_points, resource_spent, results) ==
           std::tie(other.char_id, other.dice_roll_res, other.action_points, other.resource_spent, other.results);
}

std::ostream& operator<<(std::ostream& out, const ActivatableInterface::Result& result) {
    out << "{ 'id': " << result.id() << ", ";

    if (result.dice_roll_res) {
        out << "'roll': " << static_cast<int>(result.dice_roll_res) << ", ";
    }

    out << "'action-points': " << result.action_points;
    if (result.resource_spent) {
        out << ", 'resource-spent': " << result.resource_spent;
    }
    out << ", 'action-results': [" << result.results << "] }";
    return out;
}

void Activatable::setCastType(Activatable::Cast cast_type) {
    cast_type_ = cast_type;
}

Activatable::Cast Activatable::castType() const {
    return cast_type_;
}

bool Activatable::canMiss() const {
    for (auto& action : actions_) {
        if (action.canMiss()) {
            return true;
        }
    }
    return false;
}

static void assertCharacterIsInBounds(Action::Result* res, CharacterInstance* character) {
    auto& result_pos = res->pos;
    size_t width = character->location().width();
    size_t height = character->location().height();

    if (result_pos.x >= width) {
        result_pos.x = width - 1;
    }

    if (result_pos.y >= height) {
        result_pos.y = height - 1;
    }
}

std::tuple<Activatable::Result, ErrorStatus> Activatable::use(CharacterInstance* actor,
                                                              const std::vector<Tile>& tiles,
                                                              uint8_t dice_roll_res) const {
    if (actor == nullptr) {
        return std::make_tuple(Result{}, ErrorStatus::NO_ACTOR_SET);
    }

    Result result(actor->id());

    result.action_points = actor->actionPoints() - action_cost_;

    if (canMiss()) {
        result.dice_roll_res = dice_roll_res;
    }

    if (result.action_points < 0) {
        return std::make_tuple(result, ErrorStatus::NO_ACTION_POINTS);
    }

    if (tiles.size() != actions_.size()) {
        return std::make_tuple(result, ErrorStatus::INVALID_TARGET_NUM);
    }

    for (size_t i = 0; i < tiles.size(); ++i) {
        auto [results, status] = actions_[i].getResults(*actor, tiles[i], dice_roll_res);

        if (status != ErrorStatus::OK) {
            return std::make_tuple(result, status);
        }

        for (auto& action_result : results) {
            size_t char_id = action_result.id();
            CharacterInstance* target_character = actor->map().allCharacters().safeGet(char_id);

            auto res_to_update = result.results.safeGet(char_id);

            if (res_to_update == nullptr) {
                ErrorStatus status;
                std::tie(res_to_update, status) = result.results.add(char_id,
                                                    target_character->mapPosition()[0],
                                                    target_character->hp(),
                                                    target_character->buffs());
            }

            *res_to_update += std::move(action_result);

            assertCharacterIsInBounds(res_to_update, target_character);
        }
    }

    return std::make_tuple(result, ErrorStatus::OK);
}

ErrorStatus Activatable::setCharacteristic(const std::string& which, const SetterParam& to) {
    if (which == "scaling") {
        auto value = std::get_if<std::string>(&to);
        if (!value) {
            return ErrorStatus::INVALID_ARGUMENT;
        }
        setScaling(*value);
        return ErrorStatus::OK;
    }

    auto value = std::get_if<int64_t>(&to);
    if (!value) {
        return ErrorStatus::INVALID_ARGUMENT;
    }

    if (which == "ap-cost") {
        setActivateCost(*value);
        return ErrorStatus::OK;
    } else if (which == "cast") {
        setCastType(static_cast<Cast>(*value));
        return ErrorStatus::OK;
    }

    return ErrorStatus::INVALID_SETTER;
}
}  // namespace DnD

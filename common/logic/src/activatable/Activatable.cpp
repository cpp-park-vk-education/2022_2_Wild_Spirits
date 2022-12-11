#include "Activatable.hpp"

#include "CharacterInstance.hpp"
#include "GameMap.hpp"

#include <algorithm>
#include <iterator>

namespace DnD {
ActivatableInterface::Result::Result(int ap, unsigned int resource, const std::vector<Action::Result>& input_results) :
    action_points(ap), resource_spent(resource),
    results(input_results.begin(), input_results.end()) {}

bool ActivatableInterface::Result::operator==(const Result& other) const {
    return std::tie(action_points, resource_spent, results) ==
           std::tie(other.action_points, other.resource_spent, other.results);
}

std::ostream& operator<<(std::ostream& out, const ActivatableInterface::Result& result) {
    out << "{ 'action-points': " << result.action_points;
    if (result.resource_spent) {
        out << ", 'resource-spent': " << result.resource_spent;
    }
    out << ", 'action-results': [" << result.results << "] }";
    return out;
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
    Result result;
    if (actor == nullptr) {
        return std::make_tuple(result, ErrorStatus::NO_ACTOR_SET);
    }

    result.action_points = actor->actionPoints() - action_cost_;

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

    actor->setActionPoints(result.action_points);
    return std::make_tuple(result, ErrorStatus::OK);
}
}  // namespace DnD
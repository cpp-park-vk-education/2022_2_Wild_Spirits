#include "Activatable.hpp"

#include "CharacterInstance.hpp"
#include "GameMap.hpp"

namespace DnD {
std::tuple<Activatable::Result, ErrorStatus> Activatable::use(const std::vector<Tile>& tiles,
                                                              uint8_t dice_roll_res) const {
    Result result;
    result.action_points = actor_->actionPoints() - action_cost_;

    if (result.action_points < 0) {
        return std::make_tuple(result, ErrorStatus::NO_ACTION_POINTS);
    }

    if (tiles.size() != actions_.size()) {
        return std::make_tuple(result, ErrorStatus::NOT_ENOUGH_TARGETS);
    }

    for (size_t i = 0; i < tiles.size(); ++i) {
        auto [results, status] = actions_[i].getResults(*actor_, tiles[i], dice_roll_res);

        if (status != ErrorStatus::OK) {
            return std::make_tuple(result, status);
        }

        for (auto& action_result : results) {
            size_t char_id = action_result.id();
            CharacterInstance* target_character = actor_->map().allCharacters().get(char_id);

            auto [res_to_update, status] = result.results.safeGet(char_id);

            if (status == ErrorStatus::NO_SUCH_ITEM) {
                *res_to_update = Action::Result(char_id,
                                                target_character->mapPosition()[0],
                                                target_character->hp(),
                                                target_character->buffs());
            }
        }
    }

    return std::make_tuple(result, ErrorStatus::OK);
}
}  // namespace DnD

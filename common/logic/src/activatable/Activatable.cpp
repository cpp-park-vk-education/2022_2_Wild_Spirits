#include "Activatable.hpp"

#include "CharacterInstance.hpp"

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

    return std::make_tuple(result, ErrorStatus::OK);
}
}  // namespace DnD

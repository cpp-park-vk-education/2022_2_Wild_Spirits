#include "Spell.hpp"
#include "CharacterInstance.hpp"

namespace DnD {
    std::tuple<Activatable::Result, ErrorStatus> Spell::use(CharacterInstance* character,
                                        const std::vector<Tile>& targets,
                                        uint8_t dice_roll_res) const {
        if (character && character->spellPoints() < cost()) {
            return std::make_tuple(Result{}, ErrorStatus::NO_SPELL_POINTS);
        }

        auto result = Activatable::use(character, targets, dice_roll_res);
        std::get<Result>(result).resource_spent = spell_cost_;
        return result;
    }

    ErrorStatus Spell::setCharacteristic(const std::string& which, const SetterParam& to) {
        auto status = GameEntity::setCharacteristic(which, to);
        if (status != ErrorStatus::INVALID_SETTER) {
            return status;
        }

        status = Activatable::setCharacteristic(which, to);
        if (status != ErrorStatus::INVALID_SETTER) {
            return status;
        }

        auto value = std::get_if<int64_t>(&to);
        if (!value) {
            return ErrorStatus::INVALID_ARGUMENT;
        }

        if (which == "sp-cost") {
            setCost(*value);
            return ErrorStatus::OK;
        }

        return ErrorStatus::INVALID_SETTER;
    }
}  // namespace DnD

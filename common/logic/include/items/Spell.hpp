#pragma once

#include "Activatable.hpp"

namespace DnD {
class Spell : public GameEntity, public Activatable {
 private:
    unsigned int spell_cost_;

 public:
    Spell() = default;

    Spell(size_t id) : GameEntity(id) {}

    Spell(size_t id, std::string_view name, size_t image_id,
          const std::vector<Action>& actions, unsigned int action_cost,
          std::string_view scaling, unsigned int spell_cost,
          Cast cast_type = Cast::Tile, const Info& info = {}) :
        GameEntity(id, name, image_id, info),
        Activatable(actions, action_cost, scaling, cast_type),
        spell_cost_(spell_cost) {}

    Spell(size_t id, std::string_view name, size_t image_id,
          std::vector<Action>&& actions, unsigned int action_cost,
          std::string_view scaling, unsigned int spell_cost,
          Cast cast_type = Cast::Tile, const Info& info = {}) :
        GameEntity(id, name, image_id, info),
        Activatable(std::move(actions), action_cost, scaling, cast_type),
        spell_cost_(spell_cost) {}

    unsigned int cost() const {
        return spell_cost_;
    }

    void setCost(unsigned int spell_cost) {
        spell_cost_ = spell_cost;
    }

    std::tuple<Result, ErrorStatus> use(CharacterInstance* character,
                                        const std::vector<Tile>& targets,
                                        uint8_t dice_roll_res = 0) const override;

    ErrorStatus setCharacteristic(const std::string& which, const SetterParam& to) override;
};
}  // namespace DnD

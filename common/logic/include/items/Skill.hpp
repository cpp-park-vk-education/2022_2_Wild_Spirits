#pragma once

#include "Activatable.hpp"
#include "GameEntity.hpp"
#include "TurnBased.hpp"

namespace DnD {
class Skill : public GameEntity, public Activatable {
 private:
    unsigned int cooldown_;

 public:
    Skill() = default;

    Skill(size_t id, std::string_view name, size_t image_id,
          const std::vector<Action>& actions, unsigned int action_cost,
          unsigned int cooldown, std::string_view scaling = "",
          Cast cast_type = Cast::Tile, const Info& info = {}) :
        GameEntity(id, name, image_id, info),
        Activatable(actions, action_cost, scaling, cast_type),
        cooldown_(cooldown) {}

    Skill(size_t id, std::string_view name, size_t image_id,
          std::vector<Action>&& actions, unsigned int action_cost,
          unsigned int cooldown, std::string_view scaling = "",
          Cast cast_type = Cast::Tile, const Info& info = {}) :
        GameEntity(id, name, image_id, info),
        Activatable(std::move(actions), action_cost, scaling, cast_type),
        cooldown_(cooldown) {}

    unsigned int cooldown() const {
        return cooldown_;
    }

    void setCooldown(unsigned int cooldown) {
        cooldown_ = cooldown;
    }

    ErrorStatus setCharacteristic(const std::string& which, const SetterParam& to) override;
};

class Skill_Instance : public ActivatableInterface, public Temporal<TurnStart> {
 private:
    const std::shared_ptr<const Skill> original_;

 public:
    Skill_Instance(const std::shared_ptr<const Skill>& skill) : Temporal<TurnStart>(0), original_(skill) {}

    const Skill& original() const {
        return *original_;
    }

    size_t id() const {
        return original_->id();
    }

    unsigned int activateCost() const override {
        return original_->activateCost();
    }

    const std::string& scalesBy() const override {
        return original_->scalesBy();
    }

    unsigned int cooldown() const {
        return original_->cooldown();
    }

    std::tuple<Result, ErrorStatus> use(CharacterInstance* actor, const std::vector<Tile>& tiles,
                                        uint8_t dice_roll_res = 0) const override;
};
}  // namespace DnD

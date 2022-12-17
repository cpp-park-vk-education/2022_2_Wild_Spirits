#pragma once

#include "Activatable.hpp"
#include "Item.hpp"

namespace DnD {
class ActivatableItem : public Item, public Activatable {
 public:
    ActivatableItem() = default;

    ActivatableItem(size_t id, std::string_view name, int image_id,
                    const std::vector<Action>& actions, unsigned int action_cost = 0, 
                    unsigned int cost = 0, std::string_view scaling = "",
                    Cast cast_type = Cast::Tile, const Info& info = {}) :
        Item(id, name, image_id, cost, info),
        Activatable(actions, action_cost, scaling, cast_type) {}

    ActivatableItem(size_t id, std::string_view name, int image_id,
                    std::vector<Action>&& actions, unsigned int action_cost = 0, 
                    unsigned int cost = 0, std::string_view scaling = "",
                    Cast cast_type = Cast::Tile, const Info& info = {}) :
        Item(id, name, image_id, cost, info),
        Activatable(std::move(actions), action_cost, scaling, cast_type) {}

    ErrorStatus setCharacteristic(const std::string& which, const SetterParam& to) override;
};

class Weapon : public ActivatableItem {
 public:
    Weapon() = default;

    Weapon(size_t id, std::string_view name, int image_id, const std::vector<Action>& actions,
           unsigned int action_cost = 0, unsigned int cost = 0, std::string_view scaling = "",
           Cast cast_type = Cast::Tile, const Info& info = {}) :
        ActivatableItem(id, name, image_id, actions, action_cost, cost, scaling, cast_type, info) {}

    Weapon(size_t id, std::string_view name, int image_id, std::vector<Action>&& actions,
           unsigned int action_cost = 0, unsigned int cost = 0, std::string_view scaling = "",
           Cast cast_type = Cast::Tile, const Info& info = {}) :
        ActivatableItem(id, name, image_id, std::move(actions), action_cost, cost, scaling, cast_type, info) {}
};

class Consumable : public ActivatableInterface, public DynamiclySettable {
 private:
    const std::shared_ptr<const ActivatableItem> original_;
    unsigned int uses_;

 public:
    Consumable() = default;

    Consumable(const std::shared_ptr<ActivatableItem>& item, unsigned int uses) : original_(item), uses_(uses) {}
    
    void addUses(unsigned int num) {
        uses_ += num;
    }

    void reduceUses(unsigned int num) {
        uses_ = uses_ >= num ? uses_ - num : 0;
    }

    void setUses(unsigned int num) {
        uses_ = num;
    }

    size_t id() const {
        return original_->id();
    }

    const ActivatableItem& original() const {
        return *original_;
    }

    unsigned int usesLeft() const {
        return uses_;
    }

    bool empty() const {
        return uses_ == 0;
    }

    unsigned int activateCost() const override {
        return original_->activateCost();
    }

    const std::string& scalesBy() const override {
        return original_->scalesBy();
    }

    std::tuple<Result, ErrorStatus> use(CharacterInstance* actor, const std::vector<Tile>& targets,
                                                uint8_t dice_roll_res = 0) const override;

    ErrorStatus setCharacteristic(const std::string& which, const SetterParam& to) override;
};
}  // namespace DnD

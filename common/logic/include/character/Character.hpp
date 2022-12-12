#pragma once

#include "GameEntity.hpp"
#include "Resistible.hpp"
#include "StatBased.hpp"

namespace DnD {
class Character : public GameEntity, public Resistible, public StatBased {
 protected:
    static constexpr unsigned int kDefaultExp = 500;
    static constexpr unsigned int kDefaultActionPoints = 10;
    static constexpr unsigned int kDefaultArmorClass = 10;
    static constexpr unsigned int kDefaultMaxHP = 10;

    unsigned int exp_ = kDefaultExp;

 private:
    unsigned int max_hp_ = kDefaultMaxHP;
    unsigned int max_action_points_ = kDefaultActionPoints;
    unsigned int base_armor_class_ = kDefaultArmorClass;

public:
    Character() = default;

    Character(size_t id, std::string_view name, int image_id, unsigned int max_hp,
              int exp = kDefaultExp, unsigned int ap = kDefaultActionPoints,
              unsigned int ac = kDefaultArmorClass, const Stats& stats = Stats{},
              const Info& info = {});
    
    Character(const Character& other);
    Character(Character&& other);

    Character& operator=(const Character& other);
    Character& operator=(Character&& other);
    
    void swap(Character& other);

    unsigned int exp() const {
        return exp_;
    }

    unsigned int maxActionPoints() const {
        return max_action_points_;
    }

    void setMaxActionPoints(unsigned int max_ap) {
        max_action_points_ = max_ap;
    }

    unsigned int maxHP() const {
        return max_hp_;
    }

    void setMaxHP(unsigned int max_hp) {
        max_hp_ = max_hp;
    }

    unsigned int baseArmorClass() const {
        return base_armor_class_;
    }

    void setBaseArmorClass(unsigned int armor_class) {
        base_armor_class_ = armor_class;
    }

    ErrorStatus setCharacteristic(const std::string& which, const SetterParam& to) override;
};
}  // namespace DnD

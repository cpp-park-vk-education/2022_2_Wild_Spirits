#pragma once

#include "GameEntity.hpp"
#include "Resistible.hpp"
#include "StatBased.hpp"

class Character : public GameEntity, public Resistible, public StatBased {
 protected:
    unsigned int exp_;

    static constexpr int kDefaultExp = 500;
    static constexpr unsigned int kDefaultActionPoints = 10;
    static constexpr unsigned int kDefaultArmorClass = 10;


 private:
    unsigned int max_hp_;
    unsigned int max_action_points_;
    unsigned int base_armor_class_;

public:
    Character() = default;

    Character(std::string_view name, int image_id, const Info& info, unsigned int max_hp,
              int exp = kDefaultExp, unsigned int ap = kDefaultActionPoints,
              unsigned int ac = kDefaultArmorClass, const Stats& stats = Stats{}) :
        GameEntity(name, image_id, info),
        Resistible(),
        StatBased(stats),
        exp_(exp),
        max_hp_(max_hp),
        max_action_points_(ap),
        base_armor_class_(ac) {}
    
    unsigned int maxActionPoints() const {
        return 0;
    }

    void setMaxActionPoints(unsigned int max_ap) {

    }

    unsigned int maxHP() {
        return 0;
    }

    void setMaxHP(unsigned int max_ap) {

    }

    unsigned int baseArmorClass() const {
        return 0;
    }

    void setBaseArmorClass(unsigned int) {
    
    }
};

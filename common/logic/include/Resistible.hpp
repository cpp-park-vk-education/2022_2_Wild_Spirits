#pragma once

#include <bitset>

#include "DamageTypes.hpp"

class Resistible {
 private:
    std::bitset<DamageTypes::kDamageTypesNum> resistances_;
    std::bitset<DamageTypes::kDamageTypesNum> vulnerabilities_;

 public:
    Resistible() = default;

    bool isResistantTo(uint8_t dmg_type_id) const {
        return false;
    }

    bool isVulnerableTo(uint8_t dmg_type_id) const {
        return false;
    }

    void addVulnerability(uint8_t dmg_type_id) {
        
    }

    void addResistance(uint8_t dmg_type_id) {

    }

    void removeVulnerability(uint8_t dmg_type_id) {
        
    }

    void removeResistance(uint8_t dmg_type_id) {

    }
};

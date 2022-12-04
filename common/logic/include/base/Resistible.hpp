#pragma once

#include <bitset>

#include "DamageTypeStorage.hpp"

namespace DnD {
class Resistible {
 private:
    std::bitset<DamageTypeStorage::maxNum()> resistances_;
    std::bitset<DamageTypeStorage::maxNum()> vulnerabilities_;

 public:
    static constexpr float kResistModifier = 0.5;
    static constexpr float kVulnerableModifier = 2;

    Resistible() = default;

    unsigned long resistInternal() const {
        return resistances_.to_ulong();
    }

    unsigned long vulnerInternal() const {
        return vulnerabilities_.to_ulong();
    }

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
}  // namespace DnD

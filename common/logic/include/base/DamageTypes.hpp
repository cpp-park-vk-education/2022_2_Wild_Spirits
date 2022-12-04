#pragma once

#include <array>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "DamageType.hpp"
#include "ErrorStatus.hpp"

namespace DnD {
class DamageTypeStorage {
 private:
    static constexpr uint8_t kDamageTypesNum = 32;

    std::array<std::string, kDamageTypesNum> types_;
    std::unordered_set<uint8_t> unused_ids_;

    static constexpr std::string MaximumDmgTypesExceeded() {
        return "Maximum " + std::to_string(kDamageTypesNum) + " dmg types allowed";
    }

 public:
    DamageTypeStorage();

    std::tuple<uint8_t, ErrorStatus> addDamageType(const std::string& type) {
        if (unused_ids_.empty()) {
            return std::make_tuple(0, ErrorStatus::Fail(MaximumDmgTypesExceeded()));
        }

        if (std::find(types_.begin(), types_.end(), type) != types_.end()) {
            return std::make_tuple(0, ErrorStatus::Fail("Such damage type already exists"));
        }

        uint8_t id = *unused_ids_.begin();
        unused_ids_.erase(id);
        types_[id] = type;
        return std::make_tuple(id, ErrorStatus::Ok());
    }

    ErrorStatus removeDamageType(uint8_t id) {
        if (id > kDamageTypesNum) {
            return ErrorStatus::IdOutOfRange();
        }
        
        if (unused_ids_.contains(id)) {
            return ErrorStatus::Fail("No such dmg type");
        }

        unused_ids_.insert(id);
        types_[id] = "";
        return ErrorStatus::Ok();
    } 

    const std::string& typeName(uint8_t id) const {
        return types_[id];
    }

    DamageType getDamageType(uint8_t id) const {
        return DamageType{id, types_[id]};
    }

    static constexpr uint8_t maxNum() {
        return kDamageTypesNum;
    }
};
}  // namespace DnD

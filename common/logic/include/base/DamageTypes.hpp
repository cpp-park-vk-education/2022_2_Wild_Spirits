#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "Utils.hpp"

class DamageTypes {
 private:
    std::unordered_map<std::string, uint8_t> types_;
    std::unordered_set<uint8_t> unused_ids_;

 public:
   static constexpr uint8_t kDamageTypesNum = 32;

    DamageTypes() = default;

    ErrorStatus addDamageType(const std::string& type) {
        return ErrorStatus::Fail;
    }

    void removeDamageType(const std::string& type) {

    }

    uint8_t id(const std::string& type) const {
        return 0;
    }
};

#pragma once

#include <array>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "ErrorStatus.hpp"

class DamageTypes {
 private:
    static constexpr uint8_t kDamageTypesNum = 32;

    std::array<std::string, kDamageTypesNum> types_;
    std::unordered_map<std::string, uint8_t> ids_;
    std::unordered_set<uint8_t> unused_ids_;

 public:
    DamageTypes() = default;

    ErrorStatus addDamageType(const std::string& type) {
        return ErrorStatus::Fail();
    }

    void removeDamageType(const std::string& type) {

    }

    int8_t id(const std::string& type) const {
        return 0;
    }

    const std::string& typeName(uint8_t id) const {
        return types_[id];
    }

    static constexpr uint8_t maxNum() {
        return kDamageTypesNum;
    }
};

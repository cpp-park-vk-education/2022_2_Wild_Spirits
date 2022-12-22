#pragma once

#include <array>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <vector>

#include "DamageType.hpp"
#include "ErrorStatus.hpp"

#include <gtest/gtest_prod.h>

namespace DnD {
class DamageTypeStorage {
 private:
    static constexpr uint8_t kMaxTypesNum = 32;
    static constexpr uint8_t kDefaultTypesNum = 13;

    std::unordered_set<uint8_t> unused_ids_;
    std::vector<std::string> types_;

 public:
    DamageTypeStorage();

    const auto& types() const {
        return types_;
    }

    bool filled() const {
        return unused_ids_.empty();
    }

    std::tuple<uint8_t, ErrorStatus> addDamageType(const std::string& type);

    ErrorStatus removeDamageType(uint8_t id);

    std::tuple<std::string, ErrorStatus> typeName(uint8_t id) const;

    std::tuple<DamageType, ErrorStatus> getDamageType(uint8_t id) const {
        auto [name, status] = typeName(id);
        return std::make_tuple(DamageType{id, name}, status);
    }

    int8_t typeId(const std::string& dmg_type);

    static constexpr uint8_t maxNum() {
        return kMaxTypesNum;
    }

    static constexpr uint8_t defaultNum() {
        return kDefaultTypesNum;
    }

    FRIEND_TEST(DamageTypesStorageSuite, ItIsCreatedCorrectly);
};
}  // namespace DnD

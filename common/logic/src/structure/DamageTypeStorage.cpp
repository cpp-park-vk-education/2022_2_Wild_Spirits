#include "DamageTypeStorage.hpp"

#include <numeric>
#include <iterator>
#include <vector>

namespace DnD {
DamageTypeStorage::DamageTypeStorage() : unused_ids_(),
    types_{"Slashing", "Piercing", "Bludgeoning",
           "Poison", "Acid", "Fire", "Cold",
           "Radiant", "Necrotic", "Lightning",
           "Thunder", "Force", "Psychic"}
{
    std::vector<uint8_t> tmp(kMaxTypesNum - kDefaultTypesNum);
    std::iota(tmp.begin(), tmp.end(), kDefaultTypesNum);
    std::copy(tmp.begin(), tmp.end(), std::inserter(unused_ids_, unused_ids_.begin()));
}

std::tuple<uint8_t, ErrorStatus> DamageTypeStorage::addDamageType(const std::string& type) {
    if (unused_ids_.empty()) {
        return std::make_tuple(0, ErrorStatus::MAXIMUM_DMG_TYPES_EXCEEDED);
    }

    if (std::find(types_.begin(), types_.end(), type) != types_.end()) {
        return std::make_tuple(0, ErrorStatus::ALREADY_EXISTS);
    }

    uint8_t id = *unused_ids_.begin();
    unused_ids_.erase(id);

    if (id >= types_.size()) {
        types_.resize(id + 1);
    }
    types_[id] = type;
    return std::make_tuple(id, ErrorStatus::OK);
}

int8_t DamageTypeStorage::typeId(const std::string& dmg_type) {
    auto it = std::find(types_.begin(), types_.end(), dmg_type);
    if (it == types_.end()) {
        return -1;
    }
    return it - types_.begin();
}

ErrorStatus DamageTypeStorage::removeDamageType(uint8_t id) {
    if (id > types_.size()) {
        return ErrorStatus::OUT_OF_RANGE;
    }

    if (unused_ids_.contains(id)) {
        return ErrorStatus::NO_SUCH_ITEM;
    }

    unused_ids_.insert(id);
    types_[id] = "";
    return ErrorStatus::OK;
}

std::tuple<std::string, ErrorStatus> DamageTypeStorage::typeName(uint8_t id) const {
    if (id > types_.size()) {
        return std::make_tuple("", ErrorStatus::OUT_OF_RANGE);
    }
    if (unused_ids_.contains(id)) {
        return std::make_tuple("", ErrorStatus::NO_SUCH_ITEM);
    }
    return std::make_tuple(types_[id], ErrorStatus::OK);
}
}  // namespace DnD

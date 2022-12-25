#include "NPC_Instance.hpp"

#include "Location.hpp"

#include <iterator>

namespace DnD {
NPC_Instance::NPC_Instance(size_t id, const std::shared_ptr<NPC>& original, std::unique_ptr<Position>&& pos,
                           GameMap& map, bool is_hostile, int money, const SharedStorage<Item>& items) :
        CharacterInstance(id, *original, std::move(pos), map, money, items),
        is_hostile_(is_hostile), original_(original) {
    for (const auto& [_, skill] : original->baseSkills()) {
        skills_.add(Skill_Instance(skill));
    }
}

NPC_Instance::NPC_Instance(size_t id, const std::shared_ptr<NPC>& original, GameMap& map) :
        CharacterInstance(id, *original, map) {
    for (const auto& [_, skill] : original->baseSkills()) {
        skills_.add(Skill_Instance(skill));
    }
}

NPC_Instance::NPC_Instance(NPC_Instance&& other) :
    NPC_Instance(other.id(), other.original_, std::move(other.positionObj()),
                 other.map(), other.is_hostile_, other.money(), std::move(other.items_)) {}

ErrorStatus NPC_Instance::setCharacteristic(const std::string& which, const SetterParam& to) {
    auto status = CharacterInstance::setCharacteristic(which, to);
    if (status != ErrorStatus::INVALID_SETTER) {
        return status;
    }

    auto value = std::get_if<int64_t>(&to);
    if (!value) {
        return ErrorStatus::INVALID_ARGUMENT;
    }

    if (which == "hostility") {
        setHostility(*value);
        return ErrorStatus::OK;
    }

    return ErrorStatus::INVALID_SETTER;
}
}  // namespace DnD

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

NPC_Instance::NPC_Instance(NPC_Instance&& other) :
    NPC_Instance(other.id(), other.original_, std::move(other.positionObj()),
                 other.map(), other.is_hostile_, other.money(), std::move(other.items_)) {}
}  // namespace DnD

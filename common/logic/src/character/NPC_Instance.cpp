#include "NPC_Instance.hpp"

#include "Location.hpp"

#include <iterator>

namespace DnD {
NPC_Instance::NPC_Instance(size_t id, NPC& original, std::unique_ptr<Position>&& pos,
                           GameMap& map, int money, Storage<Item*> items) :
        CharacterInstance(id, original, std::move(pos), map, money, items) {
    for (const auto& [_, skill] : original.baseSkills()) {
        skills_.add(skill);
    }
}

void NPC_Instance::setLocation(Location& loc) {
    auto& old_location = location();
    OnLocation::setLocation(loc);
    loc.npc().add(*this);
    old_location.npc().remove(id());
}
}  // namespace DnD

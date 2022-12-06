#include "NPC_Instance.hpp"

#include "Location.hpp"

namespace DnD {
void NPC_Instance::setLocation(Location& loc) {
    auto& old_location = location();
    OnLocation::setLocation(loc);
    loc.npc().add(*this);
    old_location.npc().remove(id());
}
}  // namespace DnD

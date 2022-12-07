#include "PlayerCharacter.hpp"

namespace DnD {
PlayerCharacter::PlayerCharacter(size_t id, Character& original,
                                 std::unique_ptr<Position>&& pos, GameMap& map,
                                 const Class& char_class, const Race& race,
                                 int money, Storage<Item*> items) :
    CharacterInstance(id, original, std::move(pos), map, money, items),
    class_list_(),
    race_(&race)
{
    class_list_.add(&char_class);
    for (const auto& skill : char_class.skills()) {
        skills_.add(skill);
    }
}
}  // namespace DnD
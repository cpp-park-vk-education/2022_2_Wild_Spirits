#include "PlayerCharacter.hpp"

namespace DnD {
PlayerCharacter::PlayerCharacter(size_t id, Character& original,
                                 std::unique_ptr<Position>&& pos, GameMap& map,
                                 const Class& char_class, const Race& race,
                                 int money, Storage<Item*> items) :
        CharacterInstance(id, original, std::move(pos), map, money, items),
        class_list_(),
        race_(&race) {
    class_list_.add(&char_class);
    for (auto& skill : char_class.skills()) {
        skills_.add(skill);
    }
}

const ActivatableInterface* PlayerCharacter::chooseActivatable(std::string_view action_type, size_t action_id) {
    static std::unordered_map<std::string_view, std::function<const ActivatableInterface*(size_t)>> get_action = {
        {"skill", [this] (size_t id) { return skills_.safeGet(id); }},
        {"spell", [this] (size_t id) { return spells_.safeGet(id); }},
        {"weapon", [this] (size_t id) { return weapons_.safeGet(id); }},
        {"consumable", [this] (size_t id) { return consumables_.safeGet(id); }}
    };

    if (get_action.contains(action_type)) {
        return get_action[action_type](action_id);
    }
    return nullptr;
}
}  // namespace DnD

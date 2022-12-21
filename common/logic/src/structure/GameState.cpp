#include "GameState.hpp"

#include "Dice.hpp"

#include <sstream>

namespace DnD {

GameStateImpl::GameStateImpl(SharedStorage<NPC>&& npc, SharedStorage<Item>&& items,
                             SharedStorage<ActivatableItem>&& activatables, SharedStorage<Weapon>&& weapons,
                             SharedStorage<Spell>&& spells, SharedStorage<Armor>&& armor,
                             SharedStorage<Race>&& races, SharedStorage<Class>&& classes, Config&& config) :
    npc_(std::move(npc)), items_(std::move(items)), activatables_(std::move(activatables)),
    weapons_(std::move(weapons)), spells_(std::move(spells)), armor_(std::move(armor)),
    races_(std::move(races)), classes_(std::move(classes)), config_(std::move(config)) {}

SharedStorage<NPC>& GameStateImpl::npc() {
    return npc_;
}

Storage<CharacterInstance*>& GameStateImpl::allCharacters() {
    return all_characters_;
}

SharedStorage<Race>& GameStateImpl::races() {
    return races_;
}

SharedStorage<Class>& GameStateImpl::classes() {
    return classes_;
}

SharedStorage<Item>& GameStateImpl::items() {
    return items_;
}

SharedStorage<ActivatableItem>& GameStateImpl::activatableItems() {
    return activatables_;
}

SharedStorage<Weapon>& GameStateImpl::weapons() {
    return weapons_;
}

SharedStorage<Spell>& GameStateImpl::spells() {
    return spells_;
}

SharedStorage<Armor>& GameStateImpl::armor() {
    return armor_;
}

std::tuple<Activatable::Result, ErrorStatus> LogicProcessorImpl::useActivatable(size_t actor_id, std::string_view type,
                                                                    size_t item_id, const std::vector<Tile>& target) {
    auto character = allCharacters().safeGet(actor_id);

    if (!character) {
        return std::make_tuple(Activatable::Result{}, ErrorStatus::NO_SUCH_CHARACTER);
    }

    Dice dice;
    auto [result, status] = character->use(type, item_id, target, &dice);

    if (status != ErrorStatus::OK) {
        return std::make_tuple(Activatable::Result{}, status);
    }

    return std::make_tuple(result, ErrorStatus::OK);
}

std::tuple<unsigned int, ErrorStatus> LogicProcessorImpl::rollDie(unsigned int die) const {
    Dice dice;
    if (!dice.isValid(die)) {
        return std::make_tuple(0, ErrorStatus::INVALID_ARGUMENT);
    }

    return std::make_tuple(dice.roll(die), ErrorStatus::OK);
}

std::unordered_map<size_t, size_t> LogicProcessorImpl::kill_NPC(size_t location_id, size_t npc_id) {
    return {};
}

ErrorStatus LogicProcessorImpl::distributeSkillPoints(size_t player_char_id, const StatBased::Stats& stats) {
    return ErrorStatus::UNKNOWN_ERROR;
}

ErrorStatus LogicProcessorImpl::trade(size_t first_char, size_t second_char,
                                      size_t first_item, size_t second_item) {
    return ErrorStatus::UNKNOWN_ERROR;
}

SaleResult LogicProcessorImpl::buy(size_t first_char, size_t second_char, size_t item, size_t num) {
    return SaleResult{ErrorStatus::UNKNOWN_ERROR};
}

void LogicProcessorImpl::setUpdated(GameEntityInterface& object) {
    if (!object.wasUpdated()) {
        object.toggleUpdated();
    }
}
}  // namespace DnD

#include "GameState.hpp"

#include "Dice.hpp"

#include <sstream>

namespace DnD {
SharedStorage<NPC>& GameStateImpl::npc() {
    return npc_;
}

SharedStorage<PlayerCharacter>& GameStateImpl::players() {
    return players_;
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

ErrorStatus GameStateImpl::addAction(std::string_view item_type, size_t item_id, const Action& action) {
    return ErrorStatus::UNKNOWN_ERROR;
}

ErrorStatus GameStateImpl::removeAction(std::string_view item_type, size_t item_id, size_t action_id) {
    return ErrorStatus::UNKNOWN_ERROR;
}

ErrorStatus GameStateImpl::addEffect(std::string_view item_type, size_t item_id, std::unique_ptr<Effect>&& effect) {
    return ErrorStatus::UNKNOWN_ERROR;
}

ErrorStatus GameStateImpl::removeEffect(std::string_view item_type, size_t item_id, size_t effect_id) {
    return ErrorStatus::UNKNOWN_ERROR;
}

ErrorStatus GameStateImpl::setArea(std::string_view item_type, size_t item_id, std::unique_ptr<Area>&& area) {
    return ErrorStatus::UNKNOWN_ERROR;
}

ErrorStatus GameStateImpl::setPositionType(size_t char_id, std::unique_ptr<Position>&& pos) {
    return ErrorStatus::UNKNOWN_ERROR;
}

std::tuple<std::string, ErrorStatus> LogicProcessorImpl::useActivatable(size_t actor_id, std::string_view type,
                                                                    size_t item_id, const std::vector<Tile>& target) {
    auto character = allCharacters().safeGet(actor_id);

    if (!character) {
        return std::make_tuple("", ErrorStatus::NO_SUCH_CHARACTER);
    }

    Dice dice;
    auto [result, status] = character->use(type, item_id, target, &dice);

    if (status != ErrorStatus::OK) {
        return std::make_tuple("", status);
    }

    std::stringstream stream;
    stream << result;

    return std::make_tuple(stream.str(), ErrorStatus::OK);
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

LogicProcessor::GameData LogicProcessorImpl::getUpdatedObjs() {
    GameData updated_objs;
    return updated_objs;
}
}  // namespace DnD

#include "GameState.hpp"

namespace DnD {
Storage<NPC>& GameStateImpl::npc() {
    return npc_;
}

Storage<PlayerCharacter>& GameStateImpl::players() {
    return players_;
}

Storage<Race>& GameStateImpl::races() {
    return races_;
}

Storage<Class>& GameStateImpl::classes() {
    return classes_;
}

Storage<Item>& GameStateImpl::items() {
    return items_;
}

Storage<Weapon>& GameStateImpl::weapons() {
    return weapons_;
}

Storage<Spell>& GameStateImpl::spells() {
    return spells_;
}

Storage<Armor>& GameStateImpl::armor() {
    return armor_;
}

ErrorStatus GameStateImpl::addItem(size_t char_id, std::string_view item_type, size_t item_id) {
    return ErrorStatus::Fail();
}

ErrorStatus GameStateImpl::removeItem(size_t char_id, std::string_view item_type, size_t item_id) {
    return ErrorStatus::Fail();
}

ErrorStatus GameStateImpl::addAction(std::string_view item_type, size_t item_id, const Action& action) {
    return ErrorStatus::Fail();
}

ErrorStatus GameStateImpl::removeAction(std::string_view item_type, size_t item_id, size_t action_id) {
    return ErrorStatus::Fail();
}

ErrorStatus GameStateImpl::addEffect(std::string_view item_type, size_t item_id, std::unique_ptr<Effect>&& effect) {
    return ErrorStatus::Fail();
}

ErrorStatus GameStateImpl::removeEffect(std::string_view item_type, size_t item_id, size_t effect_id) {
    return ErrorStatus::Fail();
}

ErrorStatus GameStateImpl::setArea(std::string_view item_type, size_t item_id, std::unique_ptr<Area>&& area) {
    return ErrorStatus::Fail();
}

ErrorStatus GameStateImpl::setPositionType(size_t char_id, std::unique_ptr<Position>&& pos) {
    return ErrorStatus::Fail();
}

ErrorStatus GameStateImpl::moveCharacter(size_t char_id, Tile tile) {
    return ErrorStatus::Fail();
}

ErrorStatus GameStateImpl::changeCharacteristic(std::string_view type, size_t id, std::string_view characteristic,
                                                const std::variant<std::string, size_t, int>& replacer) {
    return ErrorStatus::Fail();
}

std::tuple<std::string, ErrorStatus> LogicProcessorImpl::useActivatable(size_t actor_id, std::string_view type,
                                                                        size_t item_id, Tile target) {
    return {};
}

std::unordered_map<size_t, size_t> LogicProcessorImpl::kill_NPC(size_t location_id, size_t npc_id) {
    return {};
}

ErrorStatus LogicProcessorImpl::distributeSkillPoints(size_t player_char_id, const StatBased::Stats& stats) {
    return ErrorStatus::Fail();
}

ErrorStatus LogicProcessorImpl::trade(size_t first_char, size_t second_char,
                                      size_t first_item, size_t second_item) {
    return ErrorStatus::Fail();
}

SaleResult LogicProcessorImpl::buy(size_t first_char, size_t second_char, size_t item, size_t num) {
    return SaleResult{ErrorStatus::Fail()};
}

void LogicProcessorImpl::setUpdated(GameEntityInterface& object) {
    if (!object.wasUpdated()) {
        object.toggleUpdated();
    }
}

LogicProcessor::GameData LogicProcessorImpl::getUpdatedObjs() {
    return {};
}
}  // namespace DnD

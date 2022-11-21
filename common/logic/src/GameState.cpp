#include "GameState.hpp"

size_t GameStateImpl::createPlayerCharacter() {
    return 0;
}

size_t GameStateImpl::createNPC() {
    return 0;
}

size_t GameStateImpl::createItem() {
    return 0;
}
size_t GameStateImpl::createWeapon() {
    return 0;
}

size_t GameStateImpl::createSpell() {
    return 0;
}

size_t GameStateImpl::createArmor() {
    return 0;
} 

size_t GameStateImpl::createRace() {
    return 0;
}

size_t GameStateImpl::createCharacterClass() {
    return 0;
}

ErrorStatus GameStateImpl::addToLocation(size_t npc_id, size_t location_id, Position* pos) {
    return ErrorStatus::Fail;
}

PlayerCharacter& GameStateImpl::getPlayerCharacter(size_t ind) {
    return players_.at(ind);
}

NPC& GameStateImpl::getNPC(size_t ind) {
    return npc_types_[ind];
}

Item& GameStateImpl::getItem(size_t ind) {
    return storage_.getItem(ind);
}

Weapon& GameStateImpl::getWeapon(size_t ind) {
    return storage_.getWeapon(ind);
}

Spell& GameStateImpl::getSpell(size_t ind) {
    return storage_.getSpell(ind);
}

Armor& GameStateImpl::getArmor(size_t ind) {
    return storage_.getArmor(ind);
}

Race& GameStateImpl::getRace(size_t ind) {
    return races_[ind];
}

CharacterClass& GameStateImpl::getCharacterClass(size_t ind) {
    return classes_[ind];
}

ErrorStatus GameStateImpl::addItem(size_t char_id, std::string_view item_type, size_t item_id) {
    return ErrorStatus::Fail;
}

ErrorStatus GameStateImpl::removeItem(size_t char_id, std::string_view item_type, size_t item_id) {
    return ErrorStatus::Fail;
}

ErrorStatus GameStateImpl::addAction(std::string_view item_type, size_t item_id, const Action& action) {
    return ErrorStatus::Fail;
}

ErrorStatus GameStateImpl::removeAction(std::string_view item_type, size_t item_id, size_t action_id) {
    return ErrorStatus::Fail;
}

ErrorStatus GameStateImpl::addEffect(std::string_view item_type, size_t item_id, Effect* effect) {
    return ErrorStatus::Fail;
}

ErrorStatus GameStateImpl::removeEffect(std::string_view item_type, size_t item_id, size_t effect_id) {
    return ErrorStatus::Fail;
}

ErrorStatus GameStateImpl::setArea(std::string_view item_type, size_t item_id, Area* area) {
    return ErrorStatus::Fail;
}

ErrorStatus GameStateImpl::setPositionType(size_t char_id, Position* pos) {
    return ErrorStatus::Fail;
}

ErrorStatus GameStateImpl::moveCharacter(size_t char_id, Tile tile) {
    return ErrorStatus::Fail;
}

ErrorStatus GameStateImpl::changeCharacteristic(std::string_view type, size_t id, std::string_view characteristic,
                            const std::variant<std::string, size_t, int>& replacer) {
    return ErrorStatus::Fail;
}

Action::Result GameLogicProcessorImpl::useActivatable(size_t actor_id, std::string_view type,
                                                      size_t item_id, Tile target) {
    return Action::Result{};
}
 
std::unordered_map<size_t, size_t> GameLogicProcessorImpl::kill_NPC(size_t npc_id) {
    return {};
}

ErrorStatus GameLogicProcessorImpl::distributeSkillPoints(size_t player_char_id, const StatBased::Stats& stats) {
    return ErrorStatus::Fail;
}

ErrorStatus GameLogicProcessorImpl::trade(size_t first_char, size_t second_char,
                                          size_t first_item, size_t second_item) {
    return ErrorStatus::Fail;
}

SaleResult GameLogicProcessorImpl::buy(size_t first_char, size_t second_char, size_t item, size_t num) {
    return SaleResult{ErrorStatus::Fail};
}

#include "CharacterInstance.hpp"

#include "Dice.hpp"

int CharacterInstance::statCheckRoll(std::string_view stat) const {
    return 0;
}

int CharacterInstance::statBonus(std::string_view) const {
    return 0;
}

int CharacterInstance::armorClass() const {
    return 0;
}

std::tuple<std::vector<Action::Result>, ErrorStatus> CharacterInstance::useActivatable(std::string_view action_type,
                                size_t action_id, const std::vector<Tile>& target) {
    return Action().getResults(*this, {}); 
}

ErrorStatus CharacterInstance::trade(CharacterInstance& with, Item* give, Item* get) {
    return ErrorStatus::Fail;
}

SaleResult CharacterInstance::buyItem(std::string_view item_type, CharacterInstance& from, size_t item_id, size_t count) {
    return SaleResult{};
}

unsigned int CharacterInstance::actionPoints() {
    return action_points_;
}

void CharacterInstance::refreshActionPoints() {
    action_points_ = original_.maxActionPoints();
}

int CharacterInstance::money() {
    return money_;
}

void CharacterInstance::gainMoney(int money) {
    money_ += money;
}

void CharacterInstance::healBy(unsigned int amount) {
    hp_ += amount;
}

void CharacterInstance::takeDamage(unsigned int amount) {
    hp_ -= amount;
}

bool CharacterInstance::isAlive() {
    return hp_ > 0;
}

void CharacterInstance::resetHP() {
    hp_ = original_.maxHP();
}

int CharacterInstance::hp() {
    return hp_;
}

const std::string& CharacterInstance::info(const std::string& key) const {
    return original_.info(key);
}

std::string& CharacterInstance::info(const std::string& key) {
    return original_.info(key);
}

const std::string& CharacterInstance::name() const {
    return original_.name();
}

void CharacterInstance::setName(std::string_view name) {
    original_.setName(name);
}

size_t CharacterInstance::getImageId() const {
    return original_.getImageId();
}

void CharacterInstance::setImage(size_t image_id) {
    original_.setImage(image_id);
}

void CharacterInstance::onTurnStart() {}

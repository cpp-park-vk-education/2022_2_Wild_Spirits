#include "GameEntity.hpp"

GameEntity::GameEntity(std::string_view name, int image_id, const GameEntity::Info& info) :
    name_(name), image_id_(image_id), info_(info) {}

const std::string& GameEntity::info(const std::string& key) const {
    return info_.at(key);
}

std::string& GameEntity::info(const std::string& key) {
    return info_[key];
}

const std::string& GameEntity::name() const {
    return name_;
}
void GameEntity::setName(std::string_view name) {
    name_ = name;
}

int GameEntity::getImageId() const {
    return image_id_;
}

void GameEntity::setImage(int id) {
    image_id_ = id;
}

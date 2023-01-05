#include "GameEntity.hpp"

namespace DnD {
GameEntity::GameEntity(size_t id, std::string_view name, size_t image_id, const GameEntity::Info& info) :
    id_(id), name_(name), image_id_(image_id), info_(info) {}

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

size_t GameEntity::getImageId() const {
    return image_id_;
}

void GameEntity::setImage(size_t id) {
    image_id_ = id;
}

size_t GameEntity::id() const {
    return id_;
}
}  // namespace DnD

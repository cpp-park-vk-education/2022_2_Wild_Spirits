#pragma once

#include "GameEntity.hpp"
#include "NPC_Instance.hpp"

#include <unordered_map>

namespace DnD {
class NPC_Instance;
class NPC;
class GameMap;
class Position;

class Location : public GameEntity {
 private:
    SharedStorage<NPC_Instance> npc_;
    size_t height_;
    size_t width_;

 public:
    Location() = default;

    Location(size_t id, std::string_view name, int image_id,
            size_t height, size_t width, const Info& info = {});

    void setHeight(size_t height) {
        height_ = height;
    }

    void setWidth(size_t width) {
        width_ = width;
    }

    size_t height() const {
        return height_;
    }

    size_t width() const {
        return width_;
    }

    SharedStorage<NPC_Instance>& npc() {
        return npc_;
    }
};
}  // namespace DnD

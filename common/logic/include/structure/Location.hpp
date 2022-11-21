#pragma once

#include "GameEntity.hpp"
#include "NPC_Instance.hpp"

#include <unordered_map>

class NPC_Instance;
class NPC;
class GameMap;
class Position;

class Location : public GameEntity {
 private:
    std::unordered_map<size_t, NPC_Instance> npc_;
    size_t height_;
    size_t width_;

 public:
    Location() = default;

    Location(std::string_view name, int image_id, const Info& info,
             size_t height, size_t width);

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

    std::unordered_map<size_t, NPC_Instance>& npc() {
        return npc_;
    }

    void addNPC(size_t id, const NPC& npc, GameMap& map, Position* pos);
};

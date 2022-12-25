#pragma once

#include "GameEntity.hpp"
#include "NPC_Instance.hpp"

#include <unordered_map>

namespace DnD {
class GameMap;
class Position;

class Location : public GameEntity {
 private:
    enum class TileStatus {
        Free,
        Occupied
    };

    class TileMatrix {
     private:
        std::vector<TileStatus> tiles_;
        size_t width_ = 0;
        size_t height_ = 0;

        TileStatus& get(size_t x, size_t y);
        const TileStatus& get(size_t x, size_t y) const;
        bool cannotResize(size_t width, size_t height) const;

     public:
        TileMatrix() = default;
        TileMatrix(size_t x, size_t y);

        bool isFree(const Tile& tile) const;
        bool isFree(const std::vector<Tile>& tiles) const;

        ErrorStatus freeTile(const Tile& tile);
        ErrorStatus occupyTile(const Tile& tile);

        void clear();

        size_t width() const;
        size_t height() const;

        ErrorStatus resize(size_t width, size_t height);
    };

    SharedStorage<NPC_Instance> npc_;
    TileMatrix matrix_;

    std::vector<Tile> getNextTiles(const Tile& tile) const;
    ErrorStatus transferToOtherLocation(OnLocation* obj, Location* other, Tile pos);

    void freeTiles(const std::vector<Tile>& tiles);
    void occupyTiles(const std::vector<Tile>& tiles);

 public:
    Location() = default;

    Location(size_t id);

    Location(size_t id, std::string_view name, size_t image_id,
             size_t height, size_t width, const Info& info = {});

    Location(size_t id, std::string_view name, size_t image_id,
             size_t height, size_t width, SharedStorage<NPC_Instance>&& npc, const Info& info = {});

    ErrorStatus setHeight(size_t height);
    ErrorStatus setWidth(size_t width);
    ErrorStatus setSize(size_t width, size_t height);

    std::tuple<Tile, ErrorStatus> closestFreeTile(const OnLocation& obj, const Tile& tile, bool same_location = false);
    ErrorStatus hasValidPosition(const OnLocation& obj) const;
    bool isInBounds(const Tile& tile) const;

    std::vector<Tile> freeTiles() const;

    size_t width() const {
        return matrix_.width();
    }

    size_t height() const {
        return matrix_.height();
    }

    ErrorStatus setPosition(OnLocation& obj, const Tile& pos);
    ErrorStatus addObject(OnLocation& obj);

    template <typename ...Args>
    ErrorStatus createNPC(size_t id, Args&&... args);

    ErrorStatus removeNPC(size_t id);

    SharedStorage<NPC_Instance>& npc() {
        return npc_;
    }

    ErrorStatus setCharacteristic(const std::string& which, const SetterParam& to) override;

    friend class GameMapImpl;
};

template <typename ...Args>
inline ErrorStatus Location::createNPC(size_t id, Args&&... args) {
    auto [character, status] = npc().add(id, std::forward<Args>(args)...);
    if (status != ErrorStatus::OK) {
        return status;
    }
    status = addObject(*character);
    if (status != ErrorStatus::OK) {
        npc().remove(character->id());
        return status;
    }
    character->setLocation(this->id());
    return ErrorStatus::OK;
}
}  // namespace DnD

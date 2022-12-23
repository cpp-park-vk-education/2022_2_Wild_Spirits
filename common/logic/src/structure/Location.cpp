#include "Location.hpp"

#include "Position.hpp"
#include "NPC_Instance.hpp"
#include "GameMap.hpp"

#include <queue>

namespace DnD {
Location::Location(size_t id, std::string_view name, size_t image_id,
                   size_t height, size_t width, const Info& info) :
        GameEntity(id, name, image_id, info), matrix_(width, height) {}

Location::Location(size_t id, std::string_view name, size_t image_id,
         size_t height, size_t width, SharedStorage<NPC_Instance>&& npc, const Info& info) :
    GameEntity(id, name, image_id, info), npc_(std::move(npc)), matrix_(width, height) {}

ErrorStatus Location::setCharacteristic(const std::string& which, const SetterParam& to) {
    auto status = GameEntity::setCharacteristic(which, to);
    if (status != ErrorStatus::INVALID_SETTER) {
        return status;
    }

    auto value = std::get_if<int64_t>(&to);
    if (!value) {
        return ErrorStatus::INVALID_ARGUMENT;
    }

    if (which == "width") {
        setWidth(*value);
        return ErrorStatus::OK;
    } else if (which == "height") {
        setHeight(*value);
        return ErrorStatus::OK;
    }

    return ErrorStatus::INVALID_SETTER;
}

ErrorStatus Location::setWidth(size_t width) {
    return matrix_.resize(width, height());
}

ErrorStatus Location::setHeight(size_t height) {
    return matrix_.resize(width(), height);
}

ErrorStatus Location::setSize(size_t width, size_t height) {
    return matrix_.resize(width, height);
}

std::vector<Tile> Location::getNextTiles(const Tile& tile) const {
    std::vector<Tile> res;
    static std::vector<Offset> offsets = {
        Offset{0, 1}, Offset{0, -1}, Offset{1, 0}, Offset{-1, 0}
    };

    for (const auto& offset : offsets) {
        Tile next = tile + offset;
        if (isInBounds(next)) {
            res.push_back(next);
        }
    }

    return res;
}

ErrorStatus Location::transferToOtherLocation(OnLocation* obj, Location* other, Tile pos) {
    if (!obj || !other) {
        return ErrorStatus::INVALID_ARGUMENT;
    }

    auto [new_pos, error_status] = other->closestFreeTile(*obj, pos);
    if (error_status != ErrorStatus::OK) {
        return error_status;
    }

    for (const auto& tile : obj->occupiedTiles()) {
        matrix_.freeTile(tile);
    }

    obj->pos_->moveTo(new_pos);

    for (const auto& tile : obj->occupiedTiles()) {
        std::cout << tile << "\n";
        other->matrix_.occupyTile(tile);
    }

    return ErrorStatus::OK;
}

bool Location::isInBounds(const Tile& tile) const {
    // std::cout << "Tile " << tile << " is checked to be in " << Tile{width(), height()};
    // std::cout << std::boolalpha << " (" << (tile.x < width() && tile.y < height()) << ")\n";
    return tile.x < width() && tile.y < height();
}

std::tuple<Tile, ErrorStatus> Location::closestFreeTile(const OnLocation& obj, const Tile& tile, bool same_location) {
    Tile old_pos = obj.mapPosition()[0];
    if (same_location) {
        freeTiles(obj.occupiedTiles());
    }

    std::queue<Tile> queue;

    queue.push(tile);
    std::set<Tile> visited;

    while (!queue.empty()) {
        auto cur = queue.front();
        queue.pop();

        obj.pos_->moveTo(cur);
        if (hasValidPosition(obj) == ErrorStatus::OK) {
            obj.pos_->moveTo(old_pos);
            if (same_location) { occupyTiles(obj.occupiedTiles()); }
            return std::make_tuple(cur, ErrorStatus::OK);
        }

        for (auto tile : getNextTiles(cur)) {
            if (!visited.contains(tile)) {
                visited.insert(tile);
                queue.push(tile);
            }
        }
    }

    obj.pos_->moveTo(old_pos);
    if (same_location) { occupyTiles(obj.occupiedTiles()); }
    return std::make_tuple(Tile{}, ErrorStatus::NO_FREE_TILES);
}

void Location::freeTiles(const std::vector<Tile>& tiles) {
    for (const auto& tile : tiles) {
        matrix_.freeTile(tile);
    }
}

void Location::occupyTiles(const std::vector<Tile>& tiles) {
    for (const auto& tile : tiles) {
        matrix_.occupyTile(tile);
    }
}

std::vector<Tile> Location::freeTiles() const {
    std::vector<Tile> res;
    for (size_t x = 0; x < width(); ++x) {
        for (size_t y = 0; y < height(); ++y) {
            Tile tile{x, y};
            if (matrix_.isFree(tile)) {
                res.push_back(tile);
            }
        }
    }
    return res;
}

ErrorStatus Location::hasValidPosition(const OnLocation& obj) const {
    for (const auto& tile : obj.occupiedTiles()) {
        if (!isInBounds(tile)) {
            // std::cout << "Returning location out of bounds\n";
            return ErrorStatus::OUT_OF_LOCATION_BOUNDS;
        }

        if (!matrix_.isFree(tile)) {
            return ErrorStatus::TILE_OCCUPIED;
        }
    }

    return ErrorStatus::OK;
}

ErrorStatus Location::addObject(OnLocation& obj) {
    auto tiles = obj.occupiedTiles();

    auto status = hasValidPosition(obj);
    if (status != ErrorStatus::OK) {
        return status;
    }

    occupyTiles(tiles);

    return ErrorStatus::OK;
}

ErrorStatus Location::removeNPC(size_t id) {
    auto character = npc_.safeGet(id);
    if (!character) {
        return ErrorStatus::NO_SUCH_ITEM;
    }

    freeTiles(character->occupiedTiles());

    npc_.remove(id);
    return ErrorStatus::OK;
}

ErrorStatus Location::setPosition(OnLocation& obj, const Tile& pos) {
    auto old_tiles = obj.occupiedTiles();

    Tile old_pos = obj.mapPosition()[0];
    obj.pos_->moveTo(pos);

    auto status = hasValidPosition(obj);
    if (status != ErrorStatus::OK) {
        obj.pos_->moveTo(old_pos);
        return status;
    }

    freeTiles(old_tiles);
    occupyTiles(obj.occupiedTiles());

    return ErrorStatus::OK;
}

Location::TileMatrix::TileMatrix(size_t x, size_t y) : tiles_(x * y, TileStatus::Free), width_(x), height_(y) {}

Location::TileStatus& Location::TileMatrix::get(size_t x, size_t y) {
    return tiles_[y * width_ + x];
}

const Location::TileStatus& Location::TileMatrix::get(size_t x, size_t y) const {
    return const_cast<const TileStatus&>(const_cast<TileMatrix*>(this)->get(x, y));
}

bool Location::TileMatrix::isFree(const Tile& tile) const {
    if (tile.x >= width_ || tile.y >= height_) {
        return false;
    }
    return get(tile.x, tile.y) == TileStatus::Free;
}

bool Location::TileMatrix::isFree(const std::vector<Tile>& tiles) const {
    for (const auto& tile : tiles) {
        if (!isFree(tile)) {
            return false;
        }
    }
    return true;
}

ErrorStatus Location::TileMatrix::freeTile(const Tile& tile) {
    if (tile.x >= width_ || tile.y >= height_) {
        return ErrorStatus::OUT_OF_LOCATION_BOUNDS;
    }
    get(tile.x, tile.y) = TileStatus::Free;
    return ErrorStatus::OK;
}

ErrorStatus Location::TileMatrix::occupyTile(const Tile& tile) {
    if (tile.x >= width_ || tile.y >= height_) {
        return ErrorStatus::OUT_OF_LOCATION_BOUNDS;
    }
    get(tile.x, tile.y) = TileStatus::Occupied;
    return ErrorStatus::OK;
}

void Location::TileMatrix::clear() {
    std::fill(tiles_.begin(), tiles_.end(), TileStatus::Free);
}

size_t Location::TileMatrix::width() const {
    return width_;
}

size_t Location::TileMatrix::height() const {
    return height_;
}

bool Location::TileMatrix::cannotResize(size_t width, size_t height) const {
    for (size_t i = min(width, width_); i < width_; ++i) {
        for (size_t j = 0; j < height_; ++j) {
            if (get(i, j) == TileStatus::Occupied) {
                return true;
            }
        }
    }

    for (size_t i = 0; i < width_; ++i) {
        for (size_t j = min(height, height_); j < height_; ++j) {
            if (get(i, j) == TileStatus::Occupied) {
                return true;
            }
        }
    }
    return false;
}

ErrorStatus Location::TileMatrix::resize(size_t width, size_t height) {
    if ((width < width_ || height < height_) && cannotResize(width, height)) {
        return ErrorStatus::WOULD_ERASE_CHARACTERS;
    }

    std::vector<TileStatus> old_data(width * height, TileStatus::Free);
    std::swap(tiles_, old_data);

    std::swap(width_, width);
    std::swap(height_, height);

    for (size_t y = 0; y < min(height_, height); ++y) {
        for (size_t x = 0; x < min(width_, width); ++x)
        if (old_data[y * width + x] == TileStatus::Occupied) {
            get(x, y) = TileStatus::Occupied;
        }
    }

    return ErrorStatus::OK;
}
}  // namespace DnD

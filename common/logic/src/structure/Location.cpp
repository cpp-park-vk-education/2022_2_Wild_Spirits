#include "Location.hpp"

#include "Position.hpp"
#include "NPC_Instance.hpp"
#include "GameMap.hpp"

namespace DnD {
Location::Location(size_t id, std::string_view name, int image_id,
                   size_t height, size_t width, const Info& info) :
        GameEntity(id, name, image_id, info), matrix_(width, height) {}

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

ErrorStatus Location::addObject(OnLocation& obj) {
    auto tiles = obj.occupiedTiles();

    for (auto tile : tiles) {
        if (tile.x >= width() || tile.y >= height()) {
            return ErrorStatus::OUT_OF_LOCATION_BOUNDS;
        }

        if (!matrix_.isFree(tile)) {
            return ErrorStatus::TILE_OCCUPIED;
        }
    }

    for (const auto& tile : tiles) {
        matrix_.occupyTile(tile);
    }

    return ErrorStatus::OK;
}

ErrorStatus Location::setPosition(OnLocation& obj, const Tile& pos) {
    auto old_tiles = obj.occupiedTiles();

    Tile old_pos = obj.mapPosition()[0];
    obj.pos_->moveTo(pos);

    for (auto tile : obj.occupiedTiles()) {
        if (tile.x >= width() || tile.y >= height()) {
            obj.pos_->moveTo(old_pos);
            return ErrorStatus::OUT_OF_LOCATION_BOUNDS;
        }

        if (!matrix_.isFree(tile)) {
            obj.pos_->moveTo(old_pos);
            return ErrorStatus::TILE_OCCUPIED;
        }
    }

    for (const auto& tile : old_tiles) {
        matrix_.freeTile(tile);
    }

    for (const auto& tile : obj.occupiedTiles()) {
        matrix_.occupyTile(tile);
    }

    return ErrorStatus::OK;
}

Location::TileMatrix::TileMatrix(size_t x, size_t y) : tiles_(x * y, TileStatus::Free), width_(x), height_(y) {}

Location::TileStatus& Location::TileMatrix::get(size_t x, size_t y) {
    return tiles_[x * height_ + y];
}

const Location::TileStatus& Location::TileMatrix::get(size_t x, size_t y) const {
    return const_cast<const TileStatus&>(const_cast<TileMatrix*>(this)->get(x, y));
}

bool Location::TileMatrix::isFree(const Tile& tile) const {
    return get(tile.x, tile.y) == TileStatus::Free;
}

void Location::TileMatrix::freeTile(const Tile& tile) {
    get(tile.x, tile.y) = TileStatus::Free;
}

void Location::TileMatrix::occupyTile(const Tile& tile) {
    get(tile.x, tile.y) = TileStatus::Occupied;
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

    for (size_t i = 0; i < width_; ++i) {
        for (size_t j = 0; j < height_; ++j)
        if (old_data[i * height_ + j] == TileStatus::Occupied) {
            get(i, j) = TileStatus::Occupied;
        }
    }

    width_ = width;
    height_ = height;

    return ErrorStatus::OK;
}
}  // namespace DnD

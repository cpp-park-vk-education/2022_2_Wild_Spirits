#pragma once

#include "Area.hpp"
#include "Tile.hpp"
#include "ErrorStatus.hpp"

#include <array>

namespace DnD {
class Position {
 public:
    virtual bool isInArea(const Area& area) const = 0;

    virtual std::array<Tile, 2> mapPosition() const = 0;
    virtual Tile centerPos() const = 0;

    virtual ErrorStatus moveTo(const Tile& tile) = 0;
    virtual void moveBy(int x, int y) = 0;

    virtual std::unique_ptr<Position> clone() const = 0;

    virtual ~Position() {}
};

class TilePos : public Position {
 private:
    Tile pos_;
 
 public:
    TilePos(const Tile& tile) : pos_(tile) {}
    TilePos(size_t x, size_t y) : pos_{x, y} {}

    std::unique_ptr<Position> clone() const override {
        return std::make_unique<TilePos>(*this);
    }

    bool isInArea(const Area& area) const override {
        return area.isInArea(pos_);
    }

    std::array<Tile, 2> mapPosition() const override {
        return std::array<Tile, 2>{pos_, pos_};
    }

    Tile centerPos() const override {
        return pos_;
    }

    ErrorStatus moveTo(const Tile& tile) override {
        pos_ = tile;
        return ErrorStatus::OK;
    }

    void moveBy(int x, int y) override {
        pos_ += Offset{x, y};
    }
};

class RectangularPos : public Position {
 private:
    Tile bottom_left_;
    Tile upper_right_;
 
 public:
    RectangularPos(const Tile& b_left, const Tile& u_right) :
        bottom_left_(b_left), upper_right_(u_right) {}

    std::unique_ptr<Position> clone() const override {
        return std::make_unique<RectangularPos>(*this);
    }

    bool isInArea(const Area& area) const override {
        for (size_t x = bottom_left_.x; x <= upper_right_.x; ++x) {
            for (size_t y = bottom_left_.y; y <= upper_right_.y; ++y) {
                if (area.isInArea(Tile{x, y})) {
                    return true;
                }
            }
        }
        return false;
    }

    std::array<Tile, 2> mapPosition() const override {
        return std::array<Tile, 2>{bottom_left_, upper_right_};
    }

    Tile centerPos() const override {
        return (bottom_left_ + upper_right_) / 2;
    }

    ErrorStatus moveTo(const Tile& tile) override {
        Tile diff = upper_right_ - bottom_left_;
        bottom_left_ = tile;
        upper_right_ = bottom_left_ + diff;
        return ErrorStatus::OK;
    }

    void moveBy(int x, int y) override {
        Offset offset{x, y};
        bottom_left_ += offset;
        upper_right_ += offset;
    }
};

class PositionFactory {
 public:
    static std::unique_ptr<Position> create(const Tile& b_left, const Tile& u_right = Tile{}) {
        if (u_right == Tile{}) {
            return std::make_unique<TilePos>(b_left);
        }
        return std::make_unique<RectangularPos>(b_left, u_right);
    }
};
}  // namespace DnD

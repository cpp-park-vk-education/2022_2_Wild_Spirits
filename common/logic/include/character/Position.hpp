#pragma once

#include "Area.hpp"
#include "Tile.hpp"

#include <utility>

namespace DnD {
class Position {
 public:
    virtual bool isInArea(const Area& area) = 0;
    virtual std::pair<Tile, Tile> mapPosition() = 0;
    virtual void moveTo(const Tile& tile) = 0;
    virtual void moveBy(int x, int y) = 0;

    virtual Position* clone() const = 0;

    virtual ~Position() {}
};

class TilePos : public Position {
 private:
    Tile pos_;
 
 public:
    TilePos(const Tile& tile) : pos_(tile) {}
    TilePos(size_t x, size_t y) : pos_{x, y} {}

    Position* clone() const override {
        return new TilePos(*this);
    }

    bool isInArea(const Area& area) override {
        return false;
    }

    std::pair<Tile, Tile> mapPosition() override {
        return {};
    }

    void moveTo(const Tile& tile) override {

    }

    void moveBy(int x, int y) override {

    }
};

class RectangularPos : public Position {
 private:
    Tile bottom_left_;
    Tile upper_right_;
 
 public:
    RectangularPos(const Tile& b_left, const Tile& u_right) :
        bottom_left_(b_left), upper_right_(u_right) {}

    Position* clone() const override {
        return new RectangularPos(*this);
    }

    bool isInArea(const Area& area) override {
        return false;
    }

    std::pair<Tile, Tile> mapPosition() override {
        return {};
    }

    void moveTo(const Tile& tile) override {

    }

    void moveBy(int x, int y) override {

    }
};

class PositionFactory {
 public:
    static Position* create(const Tile& b_left, const Tile& u_right = Tile{}) {
        return new RectangularPos(b_left, u_right);
    }
};
}  // namespace DnD

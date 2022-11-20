#pragma once

#include "Area.hpp"
#include "Utils.hpp"

#include <tuple>

class Position {
 public:
    virtual bool isInArea(Area* area) = 0;
    virtual std::tuple<Tile, Tile> mapPosition() = 0;
    virtual void moveTo(const Tile& tile) = 0;
    virtual void moveBy(int x, int y) = 0;

    virtual ~Position() {}
};

class TilePos : public Position {
 private:
    Tile pos_;
 
 public:
    TilePos(const Tile& tile) : pos_(tile) {}

    bool isInArea(Area* area) override {
        return false;
    }

    std::tuple<Tile, Tile> mapPosition() override {
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

    bool isInArea(Area* area) override {
        return false;
    }

    std::tuple<Tile, Tile> mapPosition() override {
        return {};
    }

    void moveTo(const Tile& tile) override {

    }

    void moveBy(int x, int y) override {

    }
};

class PositionFactory {
 public:
    Position* createPosition(const Tile& b_left, const Tile& u_right = Tile{}) {
        return new RectangularPos(b_left, u_right);
    }
};

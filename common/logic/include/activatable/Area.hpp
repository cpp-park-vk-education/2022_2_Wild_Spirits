#pragma once

#include <vector>

#include "Utils.hpp"

class Area {
 protected:
    Tile target_;

 public:
    void setTarget(const Tile& target) {
        target_ = target;
    }

    virtual bool isInArea(const Tile& tile) const = 0;
};

class PointArea : public Area {
 public:
    PointArea() = default;

    bool isInArea(const Tile& tile) const override {
        return tile == target_;
    }
};

class RectangularArea : public Area {
 private:
    unsigned int height_;
    unsigned int width_;

 public:
    RectangularArea(unsigned int h, unsigned int w) : height_(h), width_(w) {}

    bool isInArea(const Tile& tile) const override {
        return false;
    }
};

class CustomArea : public Area {
 private:
    std::vector<Tile> tiles_;

 public:
    CustomArea(const std::vector<Tile> tiles) : tiles_(tiles) {}

    bool isInArea(const Tile& tile) const override {
        return false;
    }
};

class AreaFactory {
 public:
    static Area* createArea(int height = 0, int width = 0) {
        return new PointArea();
    }

    static Area* createArea(const std::vector<Tile>& tiles) {
        return new CustomArea(tiles);
    }
};

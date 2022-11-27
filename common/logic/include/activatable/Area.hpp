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

    virtual Area* clone() const = 0;
    virtual bool isInArea(const Tile& tile) const = 0;

    virtual ~Area() {}
};

class PointArea : public Area {
 public:
    PointArea() = default;

    Area* clone() const override {
        return new PointArea();
    }

    bool isInArea(const Tile& tile) const override {
        return tile == target_;
    }
};

class RectangularArea : public Area {
 private:
    unsigned int width_;
    unsigned int height_;

 public:
    RectangularArea(unsigned int w, unsigned int h) : width_(w), height_(h) {}

    Area* clone() const override {
        return new RectangularArea(*this);
    }

    bool isInArea(const Tile& tile) const override {
        return false;
    }
};

class CustomArea : public Area {
 private:
    std::vector<Tile> tiles_;

 public:
    CustomArea(const std::vector<Tile> tiles) : tiles_(tiles) {}

    Area* clone() const override {
        return new CustomArea(*this);
    }

    bool isInArea(const Tile& tile) const override {
        return false;
    }
};

class AreaFactory {
 public:
    static Area* create(int width = 0, int height = 0) {
        return new PointArea();
    }

    static Area* create(const std::vector<Tile>& tiles) {
        return new CustomArea(tiles);
    }
};

#pragma once

#include <vector>

#include "Tile.hpp"

namespace DnD {
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
    size_t width_;
    size_t height_;

 public:
    RectangularArea(size_t w, size_t h) : width_(w), height_(h) {}

    Area* clone() const override {
        return new RectangularArea(*this);
    }

    bool isInArea(const Tile& tile) const override {
        return false;
    }
};

class CustomArea : public Area {
 private:
    std::vector<Offset> offsets_;

 public:
    CustomArea(const std::vector<Offset> offsets) : offsets_(offsets) {}

    Area* clone() const override {
        return new CustomArea(*this);
    }

    bool isInArea(const Tile& tile) const override {
        return false;
    }
};

class AreaFactory {
 public:
    static Area* create(size_t width = 0, size_t height = 0) {
        return new PointArea();
    }

    static Area* create(const std::vector<Offset>& offsets) {
        return new CustomArea(offsets);
    }
};
}  // namespace DnD

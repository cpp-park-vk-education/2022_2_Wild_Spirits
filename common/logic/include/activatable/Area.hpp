#pragma once

#include <vector>
#include <memory>

#include "Tile.hpp"

namespace DnD {

class Area {
 protected:
    Tile target_;

 public:
    void setTarget(const Tile& target) {
        target_ = target;
    }

    virtual std::unique_ptr<Area> clone() const = 0;
    virtual bool isInArea(const Tile& tile) const = 0;

    virtual ~Area() {}
};

class PointArea : public Area {
 public:
    PointArea() = default;

    std::unique_ptr<Area> clone() const override {
        return std::make_unique<PointArea>();
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

    std::unique_ptr<Area> clone() const override {
        return std::make_unique<RectangularArea>(*this);
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

    std::unique_ptr<Area> clone() const override {
        return std::make_unique<CustomArea>(*this);
    }

    bool isInArea(const Tile& tile) const override {
        return false;
    }
};

class AreaFactory {
 public:
    static std::unique_ptr<Area> create(size_t width = 0, size_t height = 0) {
        return std::make_unique<PointArea>();
    }

    static std::unique_ptr<Area> create(const std::vector<Offset>& offsets) {
        return std::make_unique<CustomArea>(offsets);
    }
};
}  // namespace DnD

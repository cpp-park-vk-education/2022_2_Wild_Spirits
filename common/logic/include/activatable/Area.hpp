#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <cmath>

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
    virtual std::vector<Tile> tilesCovered() const = 0;

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

    std::vector<Tile> tilesCovered() const override {
        return std::vector<Tile>{target_};
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
        return tile.x <= target_.x + width_ &&
               tile.x >= (target_.x > width_ ? target_.x- width_ : 0) &&
               tile.y <= target_.y + height_ &&
               tile.y >= (target_.y > height_ ? target_.y - height_ : 0);
    }

    std::vector<Tile> tilesCovered() const override {
        std::vector<Tile> result;
        result.reserve((2 * width_ + 1) * (2 * height_ + 1));

        for (long long i = -width_; i <= static_cast<long long>(width_); ++i) {
            for (long long j = -height_; j <= static_cast<long long>(height_); ++j) {
                result.push_back(target_ + Offset{i, j});
            }
        }
        return result;
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
        for (auto offset : offsets_) {
            if (tile == target_ + offset) {
                return true;
            }
        }
        return false;
    }

    std::vector<Tile> tilesCovered() const override {
        std::vector<Tile> result(offsets_.size());
        std::transform(offsets_.begin(), offsets_.end(), result.begin(),
                       [this] (const Offset& offset) { return target_ + offset; });
        return result;
    }
};

class AreaFactory {
 public:
    static std::unique_ptr<Area> create(size_t width = 0, size_t height = 0) {
        if (height || width) {
            return std::make_unique<RectangularArea>(height, width);
        }
        return std::make_unique<PointArea>();
    }

    static std::unique_ptr<Area> create(const std::vector<Offset>& offsets) {
        return std::make_unique<CustomArea>(offsets);
    }
};
}  // namespace DnD

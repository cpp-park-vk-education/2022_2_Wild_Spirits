#pragma once

#include <cstddef>

namespace DnD {
struct Tile {
    size_t x = 0;
    size_t y = 0;

    bool operator==(const Tile& other) const {
        return x == other.x && y == other.y;
    }

    size_t distance(const Tile& other) {
        return 0;
    }

    template <typename VectorType>
    Tile operator+(const VectorType& other) {
        return Tile{x + other.x, y + other.y};
    }

    template <typename VectorType>
    Tile operator-(const VectorType& other) {
        return Tile{x - other.x, y - other.y};
    }

    template <typename VectorType>
    Tile& operator+=(const VectorType& other) {
        *this = *this + other;
        return *this;
    }

    template <typename VectorType>
    Tile& operator-=(const VectorType& other) {
        *this = *this - other;
        return *this;
    }
};

struct Offset {
    long long x;
    long long y;
};
}  // namespace DnD

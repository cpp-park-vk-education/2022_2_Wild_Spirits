#pragma once

#include <cstddef>

namespace DnD {
template <typename T>
struct Vector {
    T x = 0;
    T y = 0;

    bool operator==(const Vector& other) const {
        return x == other.x && y == other.y;
    }

    size_t distance(const Vector& other) {
        return 0;
    }

    Vector operator+(const Vector& other) {
        return Vector{x + other.x, y + other.y};
    }

    Vector operator-(const Vector& other) {
        return Vector{x - other.x, y - other.y};
    }

    Vector& operator+=(const Vector& other) {
        *this = *this + other;
        return *this;
    }

    Vector& operator-=(const Vector& other) {
        *this = *this - other;
        return *this;
    }
};

using Tile = Vector<size_t>;

using Offset = Vector<long long>;

inline Tile operator+(const Tile& tile, const Offset& offset) {
    return Tile{tile.x + offset.x, tile.y + offset.y};
}

inline Tile operator-(const Tile& tile, const Offset& offset) {
    return Tile{tile.x - offset.x, tile.y - offset.y};
}

inline Tile& operator+=(Tile& tile, const Offset& offset) {
    tile = tile + offset;
    return tile;
}

inline Tile& operator-=(Tile& tile, const Offset& offset) {
    tile = tile - offset;
    return tile;
}
}  // namespace DnD

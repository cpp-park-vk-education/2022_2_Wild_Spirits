#pragma once

#include <cstddef>

namespace DnD {

template <typename T, typename = std::enable_if<std::is_integral<T>::value>>
constexpr size_t abs(T num) {
    if constexpr (std::is_unsigned<T>::value) {
        return num;
    } else {
        return (num >= 0 ? num : -num);
    }
}

template <typename T>
constexpr T min(T a, T b) {
    return a < b ? a : b;
}

template <typename T>
constexpr T max(T a, T b) {
    return a > b ? a : b;
}

struct Tile {
    size_t x = 0;
    size_t y = 0;

    bool operator==(const Tile& other) const {
        return x == other.x && y == other.y;
    }

    size_t distance(const Tile& other) const {
        return max(x, other.x) - min(x, other.x) +
               max(y, other.y) - min(y, other.y);
    }

    template <typename VectorType>
    Tile operator+(const VectorType& other) const {
        return Tile{add_without_overflow(x, other.x),
                    add_without_overflow(y, other.y)};
    }

    template <typename VectorType>
    Tile operator-(const VectorType& other) const {
        return Tile{substract_without_overflow(x, other.x),
                    substract_without_overflow(y, other.y)};
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

    Tile operator*(size_t multiplier) {
        return Tile{x * multiplier, y * multiplier};
    }

    Tile operator/(size_t divisor) {
        return Tile{x / divisor, y / divisor};
    }

 private:
    template <typename T>
    static size_t add_without_overflow(size_t target, T other) {
        if (other < 0 && abs(other) > target) {
            return 0;
        } else {
            return target + other;
        }
    }

    template <typename T>
    static size_t substract_without_overflow(size_t target, T other) {
        if (other > 0 && abs(other) > target) {
            return 0;
        } else {
            return target - other;
        }
    }
};

struct Offset {
    long long x;
    long long y;
};
}  // namespace DnD

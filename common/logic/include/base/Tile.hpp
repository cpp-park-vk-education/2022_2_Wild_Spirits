#pragma once

#include <cstddef>

namespace DnD {

template <typename T>
constexpr T abs(T num) {
    if constexpr (std::is_unsigned<T>::value) {
        return num;
    } else {
        return (num >= 0 ? num : -num);
    }
}

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
    Tile operator+(const VectorType& other) const {
        return Tile{add_without_overflow(x, other.x),
                    add_without_overflow(y, other.y)};
    }

    template <typename VectorType>
    Tile operator-(const VectorType& other) const {
        return Tile{substract_without_overflow(x, other.x),
                    substract_without_overflow(y + other.y)};
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

#pragma once

enum class ErrorStatus {
    Ok,
    Fail
};

struct Tile {
    int x = 0;
    int y = 0;

    bool operator==(const Tile& other) const {
        return x == other.x && y == other.y;
    }

    Tile operator+(const Tile& other) {
        return Tile{x + other.x, y + other.y};
    }

    Tile operator-(const Tile& other) {
        return Tile{x - other.x, y - other.y};
    }

    Tile& operator+=(const Tile& other) {
        *this = *this + other;
        return *this;
    }

    Tile& operator-=(const Tile& other) {
        *this = *this - other;
        return *this;
    }
};

#pragma once

#include <string>

class ErrorStatus {
 private:
    std::string msg_;
    bool ok_;

    ErrorStatus(bool ok, std::string_view msg) :
        msg_(msg), ok_(ok) {}

 public:
    ErrorStatus() : ErrorStatus(false, "") {}

    bool ok() const {
        return ok_;
    }

    std::string_view msg() const {
        return msg_;
    }

    static ErrorStatus Ok(std::string_view msg = "") {
        return ErrorStatus(true, msg);
    }

    static ErrorStatus Fail(std::string_view msg = "") {
        return ErrorStatus(false, msg);
    }
};

struct Tile {
    int x = 0;
    int y = 0;

    bool operator==(const Tile& other) const {
        return x == other.x && y == other.y;
    }

    size_t distance(const Tile& other) {
        return 0;
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

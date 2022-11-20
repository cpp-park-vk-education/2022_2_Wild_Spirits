#pragma once

#include "Position.hpp"

#include <cstddef>

class GameMap;
class Location;

class OnLocation : public Position {
 private:
    Position* pos_;
    const GameMap& map_;
    size_t current_location_;

 public:
    OnLocation(Position* pos, GameMap& map) :
        pos_(pos), map_(map) {}
    
//     Location& location() {
//         return
//     }

    ~OnLocation() {
        delete pos_;
    }
};

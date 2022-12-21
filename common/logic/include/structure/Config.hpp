#pragma once

#include <cstdint>

namespace DnD {
struct Config {
    uint8_t skill_points_for_level_up = 3;
    float resistance_mod = 0.5;
    float vulnerability_mod = 2;
    uint8_t move_cost = 1;
    uint8_t default_action_points = 10;
};
}  // namespace DnD

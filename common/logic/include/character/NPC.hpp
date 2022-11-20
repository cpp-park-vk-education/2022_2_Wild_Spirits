#pragma once

#include "Character.hpp"

class Skill;

class NPC {
 private:
    std::unordered_map<int, Skill> skills_;
};

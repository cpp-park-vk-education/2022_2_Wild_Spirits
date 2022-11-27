#pragma once

#include "Character.hpp"
#include "Skill.hpp"
#include "Storage.hpp"

class NPC : public Character {
 private:
    Storage<Skill> skills_;

 public:
    NPC() = default;

    NPC(std::string_view name, int image_id, unsigned int max_hp,
        int exp = kDefaultExp, unsigned int ap = kDefaultActionPoints,
        unsigned int ac = kDefaultArmorClass, const Stats& stats = Stats{},
        const std::unordered_map<size_t, Skill>& skills = {}, const Info& info = {}) :
            Character(name, image_id, max_hp, exp, ap, ac, stats, info),
            skills_(skills) {}

    Storage<Skill>& skills() {
        return skills_;
    }
};

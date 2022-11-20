#pragma once

#include "Character.hpp"
#include "Skill.hpp"

class NPC : public Character {
 private:
    std::unordered_map<int, Skill> skills_;
 public:
    NPC(std::string_view name, int image_id, const Info& info, unsigned int max_hp,
        int exp = kDefaultExp, unsigned int ap = kDefaultActionPoints,
        unsigned int ac = kDefaultArmorClass, const Stats& stats = Stats{},
        const std::unordered_map<int, Skill>& skills = {}) :
            Character(name, image_id, info, max_hp, exp, ap, ac, stats),
            skills_(skills) {}

    void addSkill(int id, const Skill& skill) {
        skills_[id] = skill;
    }

    void removeSkill(int id) {
        skills_.erase(id);
    }

    Skill& getSkill(int id) {
        return skills_[id];
    }

    std::unordered_map<int, Skill>& skills() {
        return skills_;
    }
};

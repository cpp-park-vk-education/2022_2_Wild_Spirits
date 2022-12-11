#pragma once

#include "Character.hpp"
#include "Skill.hpp"
#include "Storage.hpp"

namespace DnD {
class NPC : public Character {
 private:
    SharedStorage<Skill> base_skills_;

 public:
    NPC() = default;

    NPC(size_t id, std::string_view name, int image_id, unsigned int max_hp,
        int exp = kDefaultExp, unsigned int ap = kDefaultActionPoints,
        unsigned int ac = kDefaultArmorClass, const Stats& stats = Stats{},
        const SharedStorage<Skill>& skills = {}, const Info& info = {}) :
            Character(id, name, image_id, max_hp, exp, ap, ac, stats, info),
            base_skills_(skills) {}

    SharedStorage<Skill>& baseSkills() {
        return base_skills_;
    }
};
}  // namespace DnD

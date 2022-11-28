#pragma once

#include "ActivatableItem.hpp"
#include "Armor.hpp"
#include "CharacterInstance.hpp"
#include "Skill.hpp"
#include "Spell.hpp"
#include "Storage.hpp"

#include <vector>
#include <list>
#include <unordered_map>

class Race : public GameEntity, public StatBased {
 public:
    Race() = default;
    Race(size_t id, std::string_view name, int image_id, const Info& info, const Stats& stats) : 
        GameEntity(id, name, image_id, info), StatBased(stats){}
};

class CharacterClass : public GameEntity {
 private:
    std::vector<Skill> skills_;

 public:
    CharacterClass() = default;
    CharacterClass(size_t id, std::string_view name, int image_id, const Info& info,
                    const std::vector<Skill> skills) :
        GameEntity(id, name, image_id, info), skills_(skills) {}

    void addSkill(const Skill& skill) {
        skills_.push_back(skill);
    }

    void removeSkill(int id) {
        skills_.erase(skills_.begin() + id);
    }

    Skill& getSkill(int id) {
        return skills_[id];
    }
};

class PlayerCharacter : public CharacterInstance {
 private:
    std::list<const CharacterClass*> class_list_;
    const Race* race_;
    const Armor* armor_;
    
    Storage<const Weapon*> weapons_;
    Storage<const Spell*> spells_;
    Storage<Consumable> consumables_;

    unsigned int spell_points_;
    unsigned int max_spell_points_;
    unsigned int level_ = 1;

 public:
    PlayerCharacter(size_t id, Character& original, Position* pos, GameMap& map,
                    const Race& race = Race(), const CharacterClass& char_class = CharacterClass(),
                    int money = 100, std::unordered_map<size_t, Item*> items = {}) :
        CharacterInstance(id, original, pos, map, money, items),
        class_list_(),
        race_(&race) {
            class_list_.push_back(&char_class);
        }

    void gainXP(unsigned int) {

    }

    unsigned int level() const {
        return level_;
    }

    void refreshSpellPoints() {
        setSpellPoints(max_spell_points_);
    }

    void setSpellPoints(unsigned int spell_points) {
        spell_points_ = spell_points;
    }

    void setMaxSpellPoints(unsigned int spell_points) {
        max_spell_points_ = spell_points;
    }

    unsigned int spellPoints() const {
        return spell_points_;
    }

    void setArmor(const Armor& armor) {
        armor_ = &armor;
    }

    const Armor* armor() const {
        return armor_;
    }

    Storage<const Weapon*>& weapons() {
        return weapons_;
    }

    Storage<const Spell*>& spells() {
        return spells_;
    }

    Storage<Consumable>& consumables() {
        return consumables_;
    }
};

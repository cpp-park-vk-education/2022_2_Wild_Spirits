#pragma once

#include "CharacterInstance.hpp"
#include "Skill.hpp"
#include "Spell.hpp"
#include "ActivatableItem.hpp"
#include "Armor.hpp"

#include <vector>
#include <list>
#include <unordered_map>

class Race : public GameEntity, public StatBased {
 public:
    Race() = default;
    Race(std::string_view name, int image_id, const Info& info, const Stats& stats) : 
        GameEntity(name, image_id, info), StatBased(stats){}
};

class CharacterClass : public GameEntity {
 private:
    std::vector<Skill> skills_;

 public:
    CharacterClass() = default;
    CharacterClass(std::string_view name, int image_id, const Info& info,
                    const std::vector<Skill> skills) :
        GameEntity(name, image_id, info), skills_(skills) {}

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

class Inventory {
 private:
    std::unordered_map<size_t, Consumable> consumables_;
    std::unordered_map<size_t, const Weapon*> weapons_;
 
 public:
    Inventory() = default;

    void addConsumable(int id, const Consumable& consumable) {
        consumables_[id] = consumable;
    }

    void removeConsumable(int id) {
        consumables_.erase(id);
    }

    Consumable& getConsumable(int id) {
        return consumables_[id];
    }

    void addSpell(int id, const Weapon& weapon) {
        weapons_[id] = &weapon;
    }

    void removeWeapon(int id) {
        weapons_.erase(id);
    }

    const Weapon* getWeapon(int id) {
        return weapons_[id];
    }
};

class PlayerCharacter : public CharacterInstance {
 private:
    std::list<const CharacterClass*> class_list_;
    const Race* race_;
    const Armor* armor_;
    Inventory inventory_;

    unsigned int spell_points_;
    unsigned int max_spell_points_;
    std::unordered_map<size_t, const Spell*> spells_;
    unsigned int level_ = 1;

 public:
    PlayerCharacter(Character& original, Position* pos, GameMap& map,
                    const Race& race, const CharacterClass& char_class,
                    int money = 100, std::unordered_map<size_t, Item*> items = {}) :
        CharacterInstance(original, pos, map, money, items),
        class_list_(),
        race_(&race) {

    }

    void gainXP(unsigned int) {

    }

    unsigned int level() const {
        return level_;
    }

    void refreshSpellPoints() {
        spell_points_ = max_spell_points_;
    }

    void setMaxSpellPoints(unsigned int spell_points) {
        max_spell_points_ = spell_points;
    }

    void setArmor(const Armor& armor) {
        armor_ = &armor;
    }

    const Armor* armor() {
        return armor_;
    }

    void addSpell(int id, const Spell& spell) {
        spells_[id] = &spell;
    }

    void removeSpell(int id) {
        spells_.erase(id);
    }

    const Spell* getSpell(int id) {
        return spells_[id];
    }

    Inventory& inventory() {
        return inventory_;
    }
};

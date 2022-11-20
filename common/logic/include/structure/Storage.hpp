#pragma once

#include <unordered_map>
#include <cstddef>

#include "ActivatableItem.hpp"
#include "Spell.hpp"
#include "Armor.hpp"

class Storage {
 private:
    std::unordered_map<size_t, Item> items_;
    std::unordered_map<size_t, Weapon> weapons_;
    std::unordered_map<size_t, Spell> spells_;
    std::unordered_map<size_t, Armor> armor_;

 public:
    void addItem(int id, const Item& item) {
        items_[id] = item;
    }

    void removeItem(int id) {
        items_.erase(id);
    }

    Item& getItem(int id) {
        return items_[id];
    }

    void addWeapon(int id, const Weapon& weapon) {
        weapons_[id] = weapon;
    }

    void removeWeapon(int id) {
        weapons_.erase(id);
    }

    Weapon& getWeapon(int id) {
        return weapons_[id];
    }

    void addConsumable(int id, const Spell& spell) {
        spells_[id] = spell;
    }

    void removeSpell(int id) {
        spells_.erase(id);
    }

    Spell& getSpell(int id) {
        return spells_[id];
    }

    void addConsumable(int id, const Armor& armor) {
        armor_[id] = armor;
    }

    void removeConsumable(int id) {
        armor_.erase(id);
    }

    Armor& getConsumable(int id) {
        return armor_[id];
    }
};

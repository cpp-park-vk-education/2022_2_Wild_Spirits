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

namespace DnD {
class Race : public GameEntity, public StatBased {
 public:
    Race() = default;
    Race(size_t id, std::string_view name, int image_id, const Info& info, const Stats& stats) : 
        GameEntity(id, name, image_id, info), StatBased(stats){}
};

class Class : public GameEntity {
 private:
    std::vector<std::shared_ptr<Skill>> skills_;

 public:
    Class() = default;
    Class(size_t id, std::string_view name, int image_id, const Info& info,
                    const std::vector<std::shared_ptr<Skill>> skills) :
        GameEntity(id, name, image_id, info), skills_(skills) {}

    auto& skills() const {
        return skills_;
    }

    void addSkill(const std::shared_ptr<Skill>& skill) {
        skills_.push_back(skill);
    }

    void addSkill(const Skill& skill) {
        skills_.push_back(std::make_shared<Skill>(skill));
    }

    void removeSkill(int id) {
        skills_.erase(skills_.begin() + id);
    }

    const std::shared_ptr<Skill>& getSkill(int id) const {
        return skills_[id];
    }
};

class PlayerCharacter : public CharacterInstance {
 private:
    Character base_;

    SharedStorage<const Class> class_list_;
    std::shared_ptr<const Race> race_;
    std::shared_ptr<const Armor> armor_ = {};
    
    SharedStorage<const Weapon> weapons_;
    SharedStorage<const Spell> spells_;
    SharedStorage<const ActivatableItem> activatables_;
    Storage<Consumable> consumables_;
    
    unsigned int spell_points_;
    unsigned int max_spell_points_;

    unsigned int level_ = 1;
    unsigned int current_exp_ = 0;

 protected:
    const ActivatableInterface* chooseActivatable(std::string_view action_type, size_t action_id) override;

 public:
    PlayerCharacter(size_t id, Character&& original, std::unique_ptr<Position>&& pos, GameMap& map,
                    std::shared_ptr<const Class> char_class, std::shared_ptr<const Race> race,
                    int money = 100, const SharedStorage<Item>& items = {});

    PlayerCharacter(const PlayerCharacter& other) = delete;
    PlayerCharacter& operator=(const PlayerCharacter& other) = delete;

    unsigned int gainXP(unsigned int exp);

    unsigned int level() const {
        return level_;
    }

    const Character& original() const override {
        return base_;
    }

    Character& original() {
        return base_;
    }

    bool isHostile() const override {
        return false;
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

    unsigned int spellPoints() const override {
        return spell_points_;
    }

    void setArmor(const std::shared_ptr<Armor>& armor) {
        armor_ = armor;
    }

    std::shared_ptr<const Armor>& armor() {
        return armor_;
    }

    int armorClass() const override;

    auto& classes() {
        return class_list_;
    }

    SharedStorage<const Weapon>& weapons() {
        return weapons_;
    }

    SharedStorage<const Spell>& spells() {
        return spells_;
    }

    SharedStorage<const ActivatableItem>& activatableItems() {
        return activatables_;
    }

    Storage<Consumable>& consumables() {
        return consumables_;
    }

    ErrorStatus setCharacteristic(const std::string& which, const SetterParam& to) override;
};
}  // namespace DnD

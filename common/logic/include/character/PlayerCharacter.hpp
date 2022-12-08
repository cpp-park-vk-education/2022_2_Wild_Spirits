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
    std::vector<Skill> skills_;

 public:
    Class() = default;
    Class(size_t id, std::string_view name, int image_id, const Info& info,
                    const std::vector<Skill> skills) :
        GameEntity(id, name, image_id, info), skills_(skills) {}

    auto& skills() const {
        return skills_;
    }

    void addSkill(const Skill& skill) {
        skills_.push_back(skill);
    }

    void removeSkill(int id) {
        skills_.erase(skills_.begin() + id);
    }

    const Skill& getSkill(int id) const {
        return skills_[id];
    }
};

class PlayerCharacter : public CharacterInstance {
 private:
    Storage<const Class*> class_list_;
    const Race* race_;
    const Armor* armor_;
    
    Storage<const Weapon*> weapons_;
    Storage<const Spell*> spells_;
    Storage<Consumable> consumables_;

    unsigned int spell_points_;
    unsigned int max_spell_points_;
    unsigned int level_ = 1;

 protected:
    const ActivatableInterface* chooseActivatable(std::string_view action_type, size_t action_id) override;

 public:
    PlayerCharacter(size_t id, Character& original, std::unique_ptr<Position>&& pos, GameMap& map,
                    const Class& char_class, const Race& race,
                    int money = 100, Storage<Item*> items = {});

    std::tuple<Activatable::Result, ErrorStatus> use(std::string_view action_type, size_t action_id,
                                                     const std::vector<Tile>& target,
                                                     const DiceInterface* dice = nullptr) override {
        return CharacterInstance::use(action_type, action_id, target, dice);
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

    int armorClass() const override {
        if (!armor_) {
            return original_.baseArmorClass();
        }

        int base = armor_->defense();

        switch (armor_->armorType()) {
            case Armor::Type::Light:
                return base + statBonus(Armor::kScaling);
            case Armor::Type::Medium:
                return base + std::min(Armor::kMaxBonus, statBonus(Armor::kScaling));
            default:
                return base;
        }
    }

    auto& classes() {
        return class_list_;
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
}  // namespace DnD

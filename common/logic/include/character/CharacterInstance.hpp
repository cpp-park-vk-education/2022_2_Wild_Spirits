#pragma once

#include "OnLocation.hpp"
#include "Character.hpp"
#include "Buff.hpp"
#include "Skill.hpp"
#include "ErrorStatus.hpp"
#include "Storage.hpp"

#include <list>
#include <unordered_map>

namespace DnD {

class DiceInterface;
class Item;

struct SaleResult {
    ErrorStatus status = ErrorStatus::UNKNOWN_ERROR;
    int seller_money;
    int buyer_money;
};

class CharacterInstance : public GameEntityInterface, public OnLocation, public TurnBased {
 protected:
    std::list<Buff> buffs_;

    SharedStorage<Item> items_;
    Storage<Skill_Instance> skills_;
 
 private:
    size_t id_;
    unsigned int action_points_;
    int hp_;
    int money_;
    bool was_updated_ = false;

    void toggleUpdated() override {
        was_updated_ = !was_updated_;
    }

    bool wasUpdated() const override {
        return was_updated_;
    }

    Character& original();

 protected:
    virtual const ActivatableInterface* chooseActivatable(std::string_view action_type, size_t action_id);

 public:
    CharacterInstance(size_t id, Character& original, std::unique_ptr<Position>&& pos,
                      GameMap& map, int money = 100, const SharedStorage<Item>& items = {});
    
    CharacterInstance(const CharacterInstance& other) = delete;
    CharacterInstance& operator=(const CharacterInstance& other) = delete;

    CharacterInstance& operator=(CharacterInstance&& other) = delete;
    CharacterInstance(CharacterInstance&& other);

    virtual ~CharacterInstance();

    int buffToStat(const std::string& stat) const;
    int statTotal(const std::string& stat) const;
    int statCheckRoll(const std::string& stat, const DiceInterface& dice) const;
    int8_t statBonus(const std::string& stat) const;
    virtual int armorClass() const;

    virtual std::tuple<Activatable::Result, ErrorStatus>
        use(std::string_view action_type, size_t action_id,
            const std::vector<Tile>& target, const DiceInterface* = nullptr);

    ErrorStatus trade(CharacterInstance& with, Item* give, Item* get);
    SaleResult buyItem(std::string_view item_type, CharacterInstance& from, size_t item_id, size_t count = 1);

    unsigned int actionPoints();
    void refreshActionPoints();
    void setActionPoints(unsigned int action_points);

    int money();
    void gainMoney(int money);

    void healBy(unsigned int amount);
    void takeDamage(unsigned int amount);
    bool isAlive();
    void resetHP();
    int hp();

    virtual bool isHostile() const {
        return false;
    }
    
    void addBuff(const Buff& buff);
    const std::list<Buff>& buffs() const;

    Storage<Skill_Instance>& skills();
    SharedStorage<Item>& items();

    float damageModifier(uint8_t damage_type) const;

    virtual const Character& original() const = 0;

    const Info& info() const override;
    std::string& info(const std::string&) override;

    const std::string& name() const override;
    void setName(std::string_view stat) override;

    size_t getImageId() const override;

    void setImage(size_t image_id) override;

    void onTurnStart() override;
    void onTurnEnd() override;

    size_t id() const override;
};
} // namespace DnD

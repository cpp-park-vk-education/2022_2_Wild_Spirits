#pragma once

#include "OnLocation.hpp"
#include "Character.hpp"
#include "Buff.hpp"
#include "Item.hpp"
#include "Action.hpp"
#include "Utils.hpp"

#include <list>
#include <unordered_map>

struct SaleResult {
    ErrorStatus status;
    int seller_money;
    int buyer_money;
};

class CharacterInstance : public GameEntityInterface, public OnLocation, public TurnBased {
 protected:
    Character& original_;
    std::list<Buff> buffs_;
    std::unordered_map<size_t, Item*> items_;
 
 private:
    unsigned int action_points_;
    int hp_;
    int money_;

 public:
    CharacterInstance(Character& original, Position* pos, GameMap& map,
                      int money = 100, std::unordered_map<size_t, Item*> items = {}) :
        OnLocation(pos, map),
        original_(original), items_(items), money_(money) {}

    int statCheckRoll(std::string_view stat) const;
    int statBonus(std::string_view) const;
    int armorClass() const;

    Action::Result useActivatable(std::string_view action_type,
                                  int action_id, const std::vector<Tile>& target);
    
    ErrorStatus trade(CharacterInstance* with, Item* give, Item* get);
    SaleResult buyItem(std::string_view item_type, CharacterInstance& from, int item_id, size_t count = 1);

    unsigned int actionPoints();
    void refreshActionPoints();

    int money();
    void gainMoney(int money);

    void healBy(unsigned int amount);
    void takeDamage(unsigned int amount);
    bool isAlive();
    void resetHP();
    int hp();

    const std::string& info(const std::string&) const override;
    std::string& info(const std::string&) override;

    const std::string& name() const override;
    void setName(std::string_view) override;

    int getImageId() const override;

    void setImage(int image_id) override;
    void onTurnStart() override;
};

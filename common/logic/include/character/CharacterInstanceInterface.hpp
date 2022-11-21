// #pragma once

// #include "GameEntity.hpp"
// #include "TurnBased.hpp"
// #include "OnLocation.hpp"
// #include "Action.hpp"
// #include "Item.hpp"


// class CharacterInstanceInterface : public GameEntityInterface,
//                                    public TurnBased,
//                                    virtual public OnLocationInterface {
//     virtual int statCheckRoll(std::string_view stat) const = 0;
//     virtual int statBonus(std::string_view) const = 0;
//     virtual int armorClass() const = 0;

//     virtual Action::Result useActivatable(std::string_view action_type,
//                                   int action_id, const std::vector<Tile>& target) = 0;
    
//     virtual ErrorStatus trade(CharacterInstanceInterface& with, Item* give, Item* get) = 0;
//     virtual SaleResult buyItem(std::string_view item_type, CharacterInstanceInterface& from, int item_id, size_t count = 1) = 0;

//     virtual unsigned int actionPoints() = 0;
//     virtual void refreshActionPoints() = 0;

//     virtual int money() = 0;
//     virtual void gainMoney(int money) = 0;

//     virtual void healBy(unsigned int amount) = 0;
//     virtual void takeDamage(unsigned int amount) = 0;
//     virtual bool isAlive() = 0;
//     virtual void resetHP() = 0;
//     virtual int hp() = 0;
// };

#pragma once

#include <cstddef>
#include <variant>

#include "Tile.hpp"
#include "PlayerCharacter.hpp"
#include "NPC.hpp"
#include "DamageTypeStorage.hpp"

#include "Config.hpp"
#include "Storage.hpp"
#include "GameMap.hpp"

namespace DnD {
class GameState {
 public:
    virtual SharedStorage<NPC>& npc() = 0;
    virtual SharedStorage<PlayerCharacter>& players() = 0;
    virtual Storage<CharacterInstance*>& allCharacters() = 0;

    virtual SharedStorage<Item>& items() = 0;
    virtual SharedStorage<ActivatableItem>& activatableItems() = 0;
    virtual SharedStorage<Weapon>& weapons() = 0;
    virtual SharedStorage<Spell>& spells() = 0;
    virtual SharedStorage<Armor>& armor() = 0;

    virtual SharedStorage<Race>& races() = 0;
    virtual SharedStorage<Class>& classes() = 0;
};

class GameStateImpl : virtual public GameState {
 private:
    SharedStorage<NPC> npc_;
    SharedStorage<PlayerCharacter> players_;
    Storage<CharacterInstance*> all_characters_;

    SharedStorage<Item> items_;
    SharedStorage<ActivatableItem> activatables_;
    SharedStorage<Weapon> weapons_;
    SharedStorage<Spell> spells_;
    SharedStorage<Armor> armor_;

    SharedStorage<Race> races_;
    SharedStorage<Class> classes_;

    Config config_;

 public:
    GameStateImpl() = default;

    SharedStorage<NPC>& npc() override;
    SharedStorage<PlayerCharacter>& players() override;
    Storage<CharacterInstance*>& allCharacters() override;

    SharedStorage<Item>& items() override;
    SharedStorage<ActivatableItem>& activatableItems() override;
    SharedStorage<Weapon>& weapons() override;
    SharedStorage<Spell>& spells() override;
    SharedStorage<Armor>& armor() override;

    SharedStorage<Race>& races() override;
    SharedStorage<Class>& classes() override;
};

class LogicProcessor : virtual public GameState {
 public:
    virtual std::tuple<Activatable::Result, ErrorStatus> useActivatable(size_t actor_id, std::string_view type,
                                                                size_t item_id, const std::vector<Tile>& tiles) = 0;
    
    virtual std::tuple<unsigned int, ErrorStatus> rollDie(unsigned int die) const = 0;

    virtual std::unordered_map<size_t, size_t> kill_NPC(size_t location_id, size_t npc_id) = 0;
    virtual ErrorStatus distributeSkillPoints(size_t player_char_id, const StatBased::Stats& stats) = 0;

    virtual ErrorStatus trade(size_t first_char, size_t second_char, size_t first_item, size_t second_item) = 0;
    virtual SaleResult buy(size_t first_char, size_t second_char, size_t item, size_t num = 1) = 0;

    virtual void setUpdated(GameEntityInterface& object) = 0;
};

class LogicProcessorImpl : public LogicProcessor, public GameStateImpl {
 public:
    LogicProcessorImpl() = default;

    std::tuple<Activatable::Result, ErrorStatus> useActivatable(size_t actor_id, std::string_view type,
                                                        size_t item_id, const std::vector<Tile>& tiles) override;
    std::tuple<unsigned int, ErrorStatus> rollDie(unsigned int die) const override;

    std::unordered_map<size_t, size_t> kill_NPC(size_t location_id, size_t npc_id) override;
    ErrorStatus distributeSkillPoints(size_t player_char_id, const StatBased::Stats& stats) override;

    ErrorStatus trade(size_t first_char, size_t second_char, size_t first_item, size_t second_item) override;
    SaleResult buy(size_t first_char, size_t second_char, size_t item, size_t num = 1) override;

   inline void setUpdated(GameEntityInterface& object) override;
};
} // namespace DnD

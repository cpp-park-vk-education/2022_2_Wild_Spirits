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

    virtual ErrorStatus addAction(std::string_view item_type, size_t item_id, const Action& action) = 0;
    virtual ErrorStatus removeAction(std::string_view item_type, size_t item_id, size_t action_id) = 0;

    virtual ErrorStatus addEffect(std::string_view item_type, size_t item_id, std::unique_ptr<Effect>&& effect) = 0;
    virtual ErrorStatus removeEffect(std::string_view item_type, size_t item_id, size_t effect_id) = 0;

    virtual ErrorStatus setArea(std::string_view item_type, size_t item_id, std::unique_ptr<Area>&& area) = 0;
    virtual ErrorStatus setPositionType(size_t char_id, std::unique_ptr<Position>&& pos) = 0;
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

    DamageTypeStorage damage_types_;

    Config config_;
    GameMap* map_;

 public:
    GameStateImpl() = default;
    GameStateImpl(GameMap* map) : map_(map) {}

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

    ErrorStatus addAction(std::string_view item_type, size_t item_id, const Action& action) override;
    ErrorStatus removeAction(std::string_view item_type, size_t item_id, size_t action_id) override;

    ErrorStatus addEffect(std::string_view item_type, size_t item_id, std::unique_ptr<Effect>&& effect) override;
    ErrorStatus removeEffect(std::string_view item_type, size_t item_id, size_t effect_id) override;

    ErrorStatus setArea(std::string_view item_type, size_t item_id, std::unique_ptr<Area>&& area) override;
    ErrorStatus setPositionType(size_t char_id, std::unique_ptr<Position>&& pos) override;
};

class LogicProcessor : virtual public GameState {
 protected:
    struct GameData {
        size_t current_location;

        std::unordered_map<std::string, size_t> damage_types;

        Storage<NPC*> npc;
        Storage<PlayerCharacter*> players;

        Storage<Item*> items;
        Storage<Weapon*> weapons;
        Storage<Spell*> spells;
        Storage<Armor*> armor;

        Storage<Race*> races;
        Storage<Class*> classes;

        Storage<Location*> locations;
    };

 public:
    virtual std::tuple<std::string, ErrorStatus> useActivatable(size_t actor_id, std::string_view type,
                                                                size_t item_id, const std::vector<Tile>& tiles) = 0;
 
    virtual std::unordered_map<size_t, size_t> kill_NPC(size_t location_id, size_t npc_id) = 0;
    virtual ErrorStatus distributeSkillPoints(size_t player_char_id, const StatBased::Stats& stats) = 0;

    virtual ErrorStatus trade(size_t first_char, size_t second_char, size_t first_item, size_t second_item) = 0;
    virtual SaleResult buy(size_t first_char, size_t second_char, size_t item, size_t num = 1) = 0;

    virtual void setUpdated(GameEntityInterface& object) = 0;
    virtual GameData getUpdatedObjs() = 0;
};

class LogicProcessorImpl : public LogicProcessor, public GameStateImpl {
 public:
    LogicProcessorImpl() = default;

    std::tuple<std::string, ErrorStatus> useActivatable(size_t actor_id, std::string_view type,
                                                        size_t item_id, const std::vector<Tile>& tiles) override;
 
    std::unordered_map<size_t, size_t> kill_NPC(size_t location_id, size_t npc_id) override;
    ErrorStatus distributeSkillPoints(size_t player_char_id, const StatBased::Stats& stats) override;

    ErrorStatus trade(size_t first_char, size_t second_char, size_t first_item, size_t second_item) override;
    SaleResult buy(size_t first_char, size_t second_char, size_t item, size_t num = 1) override;

    void setUpdated(GameEntityInterface& object) override;
    GameData getUpdatedObjs() override;
};
} // namespace DnD

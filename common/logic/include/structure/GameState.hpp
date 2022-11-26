#pragma once

#include <cstddef>
#include <variant>

#include "Utils.hpp"
#include "PlayerCharacter.hpp"
#include "NPC.hpp"
#include "DamageTypes.hpp"

#include "Config.hpp"
#include "Storage.hpp"
#include "GameMap.hpp"

class GameState {
 public:
    virtual Storage<NPC>& npc() = 0;
    virtual Storage<PlayerCharacter>& players() = 0;

    virtual Storage<Item>& items() = 0;
    virtual Storage<Weapon>& weapons() = 0;
    virtual Storage<Spell>& spells() = 0;
    virtual Storage<Armor>& armor() = 0;

    virtual Storage<Race>& races() = 0;
    virtual Storage<CharacterClass>& classes() = 0;

    virtual ErrorStatus addToLocation(size_t npc_id, size_t location_id, Position* pos) = 0;

    virtual ErrorStatus addItem(size_t char_id, std::string_view item_type, size_t item_id) = 0;
    virtual ErrorStatus removeItem(size_t char_id, std::string_view item_type, size_t item_id) = 0;

    virtual ErrorStatus addAction(std::string_view item_type, size_t item_id, const Action& action) = 0;
    virtual ErrorStatus removeAction(std::string_view item_type, size_t item_id, size_t action_id) = 0;

    virtual ErrorStatus addEffect(std::string_view item_type, size_t item_id, Effect* effect) = 0;
    virtual ErrorStatus removeEffect(std::string_view item_type, size_t item_id, size_t effect_id) = 0;

    virtual ErrorStatus setArea(std::string_view item_type, size_t item_id, Area* area) = 0;
    virtual ErrorStatus setPositionType(size_t char_id, Position* pos) = 0;

    virtual ErrorStatus moveCharacter(size_t char_id, Tile tile) = 0;

    virtual ErrorStatus changeCharacteristic(std::string_view type, size_t id, std::string_view characteristic,
                                      const std::variant<std::string, size_t, int>& replacer) = 0;
};

class GameStateImpl : public GameState {
 private:
    Storage<NPC> npc_;
    Storage<PlayerCharacter> players_;

    Storage<Item> items_;
    Storage<Weapon> weapons_;
    Storage<Spell> spells_;
    Storage<Armor> armor_;

    Storage<Race> races_;
    Storage<CharacterClass> classes_;

    DamageTypes damage_types_;

    Config config_;
    GameMap* map_;

 public:
    GameStateImpl(GameMap* map) : map_(map) {}

    ~GameStateImpl() {
        delete map_;
    }

    Storage<NPC>& npc() override;
    Storage<PlayerCharacter>& players() override;

    Storage<Item>& items() override;
    Storage<Weapon>& weapons() override;
    Storage<Spell>& spells() override;
    Storage<Armor>& armor() override;

    Storage<Race>& races() override;
    Storage<CharacterClass>& classes() override;

    ErrorStatus addToLocation(size_t npc_id, size_t location_id, Position* pos) override;

    ErrorStatus addItem(size_t char_id, std::string_view item_type, size_t item_id) override;
    ErrorStatus removeItem(size_t char_id, std::string_view item_type, size_t item_id) override;

    ErrorStatus addAction(std::string_view item_type, size_t item_id, const Action& action) override;
    ErrorStatus removeAction(std::string_view item_type, size_t item_id, size_t action_id) override;

    ErrorStatus addEffect(std::string_view item_type, size_t item_id, Effect* effect) override;
    ErrorStatus removeEffect(std::string_view item_type, size_t item_id, size_t effect_id) override;

    ErrorStatus setArea(std::string_view item_type, size_t item_id, Area* area) override;
    ErrorStatus setPositionType(size_t char_id, Position* pos) override;

    ErrorStatus moveCharacter(size_t char_id, Tile tile) override;

    ErrorStatus changeCharacteristic(std::string_view type, size_t id, std::string_view characteristic,
                                     const std::variant<std::string, size_t, int>& replacer) override;
};


class GameLogicProcessor : public GameState {
 public:
    virtual Action::Result useActivatable(size_t actor_id, std::string_view type, size_t item_id, Tile target) = 0;
 
    virtual std::unordered_map<size_t, size_t> kill_NPC(size_t npc_id) = 0;
    virtual ErrorStatus distributeSkillPoints(size_t player_char_id, const StatBased::Stats& stats) = 0;

    virtual ErrorStatus trade(size_t first_char, size_t second_char, size_t first_item, size_t second_item) = 0;
    virtual SaleResult buy(size_t first_char, size_t second_char, size_t item, size_t num = 1) = 0;
};

class GameLogicProcessorImpl : public GameLogicProcessor, public GameStateImpl {
 public:
    GameLogicProcessorImpl() = default;

    Action::Result useActivatable(size_t actor_id, std::string_view type, size_t item_id, Tile target) override;
 
    std::unordered_map<size_t, size_t> kill_NPC(size_t npc_id) override;
    ErrorStatus distributeSkillPoints(size_t player_char_id, const StatBased::Stats& stats) override;

    ErrorStatus trade(size_t first_char, size_t second_char, size_t first_item, size_t second_item) override;
    SaleResult buy(size_t first_char, size_t second_char, size_t item, size_t num = 1) override;
};

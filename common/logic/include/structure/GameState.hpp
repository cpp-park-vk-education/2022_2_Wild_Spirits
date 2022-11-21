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
    virtual size_t createPlayerCharacter() = 0;
    virtual size_t createNPC() = 0;
    virtual size_t createItem() = 0;
    virtual size_t createWeapon() = 0;
    virtual size_t createSpell() = 0;
    virtual size_t createArmor() = 0;
    virtual size_t createRace() = 0;
    virtual size_t createCharacterClass() = 0;

    virtual ErrorStatus addToLocation(size_t npc_id, size_t location_id, Position* pos) = 0;

    virtual PlayerCharacter& getPlayerCharacter(size_t ind) = 0;
    virtual NPC& getNPC(size_t ind) = 0;
    virtual Item& getItem(size_t ind) = 0;
    virtual Weapon& getWeapon(size_t ind) = 0;
    virtual Spell& getSpell(size_t ind) = 0;
    virtual Armor& getArmor(size_t ind) = 0;
    virtual Race& getRace(size_t ind) = 0;
    virtual CharacterClass& getCharacterClass(size_t ind) = 0;

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
    std::unordered_map<size_t, PlayerCharacter> players_;
    std::unordered_map<size_t, NPC> npc_types_;
    std::unordered_map<size_t, CharacterClass> classes_;
    std::unordered_map<size_t, Race> races_;

    DamageTypes damage_types_;

    Storage storage_;
    Config config_;
    GameMap* map_;

 public:
    GameStateImpl(GameMap* map) : map_(map) {}

    ~GameStateImpl() {
        delete map_;
    }

    size_t createPlayerCharacter() override;
    size_t createNPC() override;
    size_t createItem() override;
    size_t createWeapon() override;
    size_t createSpell() override;
    size_t createArmor() override;
    size_t createRace() override;
    size_t createCharacterClass() override;

    ErrorStatus addToLocation(size_t npc_id, size_t location_id, Position* pos) override;

    PlayerCharacter& getPlayerCharacter(size_t ind) override;
    NPC& getNPC(size_t ind) override;
    Item& getItem(size_t ind) override;
    Weapon& getWeapon(size_t ind) override;
    Spell& getSpell(size_t ind) override;
    Armor& getArmor(size_t ind) override;
    Race& getRace(size_t ind) override;
    CharacterClass& getCharacterClass(size_t ind) override;

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
                              const std::variant<std::string, size_t, int>& replacer);
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
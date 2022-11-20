#pragma once

#include <cstddef>
#include <variant>

#include "Utils.hpp"
#include "PlayerCharacter.hpp"
#include "NPC.hpp"
#include "DamageTypes.hpp"

#include "Config.hpp"
#include "Storage.hpp"

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

    virtual void addToLocation(size_t npc_id, size_t location_id, Position* pos) = 0;

    virtual PlayerCharacter& getPlayerCharacter(size_t ind) = 0;
    virtual NPC& getNPC(size_t ind) = 0;
    virtual Item& getItem(size_t ind) = 0;
    virtual Weapon& getWeapon(size_t ind) = 0;
    virtual Spell& getSpell(size_t ind) = 0;
    virtual Armor& getArmor(size_t ind) = 0;
    virtual Race& getRace(size_t ind) = 0;
    virtual CharacterClass& getCharacterClass(size_t ind) = 0;

    virtual void addItem(size_t char_id, std::string_view item_type, size_t item_id) = 0;
    virtual void removeItem(size_t char_id, std::string_view item_type, size_t item_id) = 0;

    virtual void addAction(std::string_view item_type, size_t item_id, const Action& action) = 0;
    virtual void removeAction(std::string_view item_type, size_t item_id, size_t action_id) = 0;

    virtual void addEffect(std::string_view item_type, size_t item_id, Effect* effect) = 0;
    virtual void removeEffect(std::string_view item_type, size_t item_id, size_t effect_id) = 0;

    virtual void setArea(std::string_view item_type, size_t item_id, Area* area) = 0;
    virtual void setPositionType(size_t char_id, Position* pos) = 0;

    virtual void moveCharacter(size_t char_id, Tile tile) = 0;

    virtual void changeCharacteristic(std::string_view type, size_t id, std::string_view characteristic,
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
    GameMap map_;

 public:
    GameStateImpl() = default;

    size_t createPlayerCharacter() override;
    size_t createNPC() override;
    size_t createItem() override;
    size_t createWeapon() override;
    size_t createSpell() override;
    size_t createArmor() override;
    size_t createRace() override;
    size_t createCharacterClass() override;

    void addToLocation(size_t npc_id, size_t location_id, Position* pos) override;

    PlayerCharacter& getPlayerCharacter(size_t ind) override;
    NPC& getNPC(size_t ind) override;
    Item& getItem(size_t ind) override;
    Weapon& getWeapon(size_t ind) override;
    Spell& getSpell(size_t ind) override;
    Armor& getArmor(size_t ind) override;
    Race& getRace(size_t ind) override;
    CharacterClass& getCharacterClass(size_t ind) override;

    void addItem(size_t char_id, std::string_view item_type, size_t item_id) override;
    void removeItem(size_t char_id, std::string_view item_type, size_t item_id) override;

    void addAction(std::string_view item_type, size_t item_id, const Action& action) override;
    void removeAction(std::string_view item_type, size_t item_id, size_t action_id) override;

    void addEffect(std::string_view item_type, size_t item_id, Effect* effect) override;
    void removeEffect(std::string_view item_type, size_t item_id, size_t effect_id) override;

    void setArea(std::string_view item_type, size_t item_id, Area* area) override;
    void setPositionType(size_t char_id, Position* pos) override;

    void moveCharacter(size_t char_id, Tile tile) override;

    void changeCharacteristic(std::string_view type, size_t id, std::string_view characteristic,
                                      const std::variant<std::string, size_t, int>& replacer);
};


class GameLogicProcessor : public GameState {
 public:
    virtual Action::Result useActivatable(size_t actor_id, std::string_view type, size_t item_id, Tile target) = 0;
 
    virtual std::unordered_map<size_t, size_t> kill_NPC(size_t npc_id) = 0;
    virtual void distributeSkillPoints(size_t player_char_id, const WithStats::Stats& stats) = 0;

    virtual ErrorStatus trade(size_t first_char, size_t second_char, size_t first_item, size_t second_item) = 0;
    virtual SaleResult buy(size_t first_char, size_t second_char, size_t item, size_t num = 1) = 0;
};

class GameLogicProcessorImpl : public GameLogicProcessor, public GameStateImpl {
 public:
    GameLogicProcessorImpl() = default;

    Action::Result useActivatable(size_t actor_id, std::string_view type, size_t item_id, Tile target) override;
 
    std::unordered_map<size_t, size_t> kill_NPC(size_t npc_id) override;
    void distributeSkillPoints(size_t player_char_id, const WithStats::Stats& stats) override;

    ErrorStatus trade(size_t first_char, size_t second_char, size_t first_item, size_t second_item) override;
    SaleResult buy(size_t first_char, size_t second_char, size_t item, size_t num = 1) override;
};

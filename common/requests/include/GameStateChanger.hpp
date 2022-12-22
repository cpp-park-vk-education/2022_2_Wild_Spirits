#pragma once

#include <tuple>
#include <string>
#include "nlohmann/json.hpp"
#include <vector>

#include "GameState.hpp"
#include "Activatable.hpp"
#include "GameEntity.hpp"
#include "Character.hpp"
#include "CharacterInstance.hpp"
#include "NPC_Instance.hpp"
#include "PlayerCharacter.hpp"


using nlohmann::json;
//new entities creation
//GameEntity interface (name, image , info)
//Activatable (cast_type, scaling, activation cost)
//Character (hp_max, max_actionPoints, base_armor_class, stats)
//NPC (skills)
//CharacterInstance(actionPoints, hp, armor_class, Position)
//NPC_instance (turnHostile, turnFriendly)
//PlayerCharacter(gainXP)
//Skill (castCost)
//Consumable (uses)

struct ChangeHandler;

class GameStateChanger{
private:
    DnD::GameState &gamestate;
    DnD::GameMap &game_map;
    std::vector<std::unique_ptr<ChangeHandler>> handlers;

    bool set_field(json changes){

    }
protected:


//    friend ChangeHandler;
public:

    GameStateChanger(DnD::GameState &gamestate, DnD::GameMap &game_map);
    bool makechange(std::tuple<std::size_t ,std::string, std::string> setter_params);
    bool makechange(std::tuple<std::string, std::string> setter_params);
    bool makechange(std::string request_part);
    bool makechange(nlohmann::json request_part);
};

struct ChangeHandler{
    virtual bool CanHandle(json changes) = 0;
    virtual void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) = 0;
    virtual ~ChangeHandler() {
    }
};


//For GameEntityInterface setters
struct ImageHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("image");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override {

    }
};

struct NameHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("name");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};

struct InfoHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("info");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};

//For Activatable setters
struct CastTypeHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("cast_type");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{
        changing_gamestate.activatableItems().get(changes["id"]).setCastType((changes["cast_type"] == "tile")? DnD::Activatable::Cast::Tile : DnD::Activatable::Cast::Self);
    }
};

struct ScalingHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("scaling");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{
        changing_gamestate.activatableItems().get(changes["id"]).setScaling(changes["scaling"]);
    }
};

struct ActivationCostHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("activation_cost");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{
        changing_gamestate.activatableItems().get(changes["id"]).setActivateCost(changes["activation_cost"]);
    }
};
//For Character setters
struct HpMaxHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("hp_max");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};

struct ApMaxHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("ap_max");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};

struct BaseArmorHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("base_armor");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};

struct StatsHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("stats");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};
//For NPC setters
struct SkillsHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("skills");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};
//For CharacterInstance setters
struct ApHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("ap");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{
        changing_gamestate.allCharacters().get(changes["id"]) -> setActionPoints(changes["ap"]);
    }
};

struct HpHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("hp");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{
        changing_gamestate.allCharacters().get(changes["id"]) -> setHP(changes["hp"]);
    }
};

struct ArmorHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("armor");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};

struct PositionHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("position");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{
        DnD::Tile new_position(changes["x"], changes["y"]);
        game_map.allCharacters().get(changes["id"])->moveTo(new_position);
    }
};
//For NPC_instance setters

struct HostileHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("hostile");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};

//For PlayerCharacter setters
struct XPHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("gain_XP");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};
//For Skill setters
struct CastCostHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("cast_cost");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};

//For Consumable setters

struct UsesHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("uses");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate, DnD::GameMap& game_map) override{

    }
};
